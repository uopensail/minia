#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# `Minia` - A C++ tool for feature transformation and hashing
# Copyright (C) 2019 - present Uopensail <timepi123@gmail.com>
# This software is distributed under the GNU Affero General Public License (AGPL3.0)
# For more information, please visit: https://www.gnu.org/licenses/agpl-3.0.html
#
# This program is free software: you are free to redistribute and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Refer to the
# GNU Affero General Public License for more details.
#

import os
import platform
import shutil
import subprocess
import sys
from pathlib import Path

from setuptools import Extension, find_packages, setup
from setuptools.command.build_ext import build_ext


def get_requires(filename):
    """Read requirements from file"""
    requirements = []
    try:
        with open(filename, "rt") as req_file:
            for line in req_file.read().splitlines():
                if not line.strip().startswith("#"):
                    requirements.append(line)
    except FileNotFoundError:
        pass
    return requirements


class CMakeExtension(Extension):
    """CMake extension class"""
    def __init__(self, name: str, sourcedir: str = "") -> None:
        super().__init__(name, sources=[])
        self.sourcedir = os.fspath(Path(sourcedir).resolve())


class CMakeBuild(build_ext):
    """Custom build_ext command for CMake extensions"""
    
    def __init__(self, dist):
        super().__init__(dist)
        self.system = platform.system()
        self.lib_ext = self._get_lib_extension()
        
    def _get_lib_extension(self):
        """Get dynamic library extension for current platform"""
        if self.system == "Darwin":
            return ".dylib"
        elif self.system == "Windows":
            return ".dll"
        else:
            return ".so"
    
    def _fix_macos_install_name(self, lib_file):
        """Fix macOS dynamic library install_name"""
        try:
            # Change install_name to relative path
            subprocess.run([
                "install_name_tool", 
                "-id", 
                f"@loader_path/{lib_file.name}",
                str(lib_file)
            ], check=True, capture_output=True)
        except subprocess.CalledProcessError:
            pass  # Ignore errors, might be static lib or other reasons
    
    def _copy_extension_to_target(self, build_dir, target_dir):
        """Copy the built extension to target directory"""
        # Look for the Python extension in build directory
        extension_patterns = [
            "pyminia*.so",
            "pyminia*.pyd", 
            "pyminia*.dylib"
        ]
        
        for pattern in extension_patterns:
            for ext_file in build_dir.rglob(pattern):
                if ext_file.is_file():
                    target_file = target_dir / ext_file.name
                    try:
                        shutil.copy2(ext_file, target_file)
                        print(f"Copied extension: {ext_file.name} -> {target_file}")
                        return True
                    except Exception as e:
                        print(f"Warning: Failed to copy extension {ext_file}: {e}")
        
        return False
    
    def build_extension(self, ext: CMakeExtension) -> None:
        """Build the CMake extension"""
        # Get extension output path
        ext_fullpath = Path.cwd() / self.get_ext_fullpath(ext.name)
        extdir = ext_fullpath.parent.resolve()
        extdir.mkdir(parents=True, exist_ok=True)

        # Build configuration
        debug = int(os.environ.get("DEBUG", 0)) if self.debug is None else self.debug
        cfg = "Debug" if debug else "Release"
        
        # Create build directory
        build_temp = Path(self.build_temp).resolve() / ext.name
        build_temp.mkdir(parents=True, exist_ok=True)
        
        print(f"Extension output directory: {extdir}")
        print(f"Build temp directory: {build_temp}")
        print(f"Source directory: {ext.sourcedir}")
        
        # CMake arguments
        cmake_args = [
            f"-DCMAKE_BUILD_TYPE={cfg}",
            "-DBUILD_PYTHON_BINDINGS=ON",
            "-DBUILD_SHARED_LIBS=ON",
            "-DBUILD_STATIC_LIBS=ON",
            f"-DPYTHON_EXECUTABLE={sys.executable}",
            # Set output directories relative to build directory
            f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={build_temp}",
            f"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY={build_temp}",
            f"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY={build_temp}",
        ]
        
        # Force generator based on platform
        if self.system == "Windows":
            # Use Visual Studio on Windows
            plat_to_cmake = {
                "win32": "Win32",
                "win-amd64": "x64", 
                "win-arm32": "ARM",
                "win-arm64": "ARM64",
            }
            cmake_args += ["-A", plat_to_cmake.get(self.plat_name, "x64")]
            # For multi-config generators, set per-config output directories
            cmake_args += [
                f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY_{cfg.upper()}={build_temp}",
                f"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY_{cfg.upper()}={build_temp}",
                f"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_{cfg.upper()}={build_temp}",
            ]
        else:
            # Force Unix Makefiles on Unix-like systems
            cmake_args += ["-G", "Unix Makefiles"]
        
        build_args = []
        
        # Add config for multi-config generators (Windows)
        if self.system == "Windows":
            build_args += ["--config", cfg]
        
        # Add environment CMake arguments if any
        if "CMAKE_ARGS" in os.environ:
            cmake_args += [item for item in os.environ["CMAKE_ARGS"].split(" ") if item]
        
        # macOS cross-compile support
        if self.system == "Darwin":
            import re
            archs = re.findall(r"-arch (\S+)", os.environ.get("ARCHFLAGS", ""))
            if archs:
                cmake_args += ["-DCMAKE_OSX_ARCHITECTURES={}".format(";".join(archs))]
        
        # Parallel build
        if "CMAKE_BUILD_PARALLEL_LEVEL" not in os.environ:
            if hasattr(self, "parallel") and self.parallel:
                build_args += [f"-j{self.parallel}"]
            else:
                import multiprocessing
                build_args += [f"-j{multiprocessing.cpu_count()}"]

        # Setup environment - remove CMAKE_GENERATOR to avoid conflicts
        env = os.environ.copy()
        env.pop("CMAKE_GENERATOR", None)  # Remove any existing generator setting

        # Execute CMake configure
        print(f"CMake configure: cmake {ext.sourcedir} {' '.join(cmake_args)}")
        print(f"Working directory: {build_temp}")
        
        try:
            subprocess.run(
                ["cmake", ext.sourcedir] + cmake_args, 
                cwd=build_temp, 
                env=env,
                check=True
            )
            print("CMake configure succeeded")
        except subprocess.CalledProcessError as e:
            print(f"CMake configure failed with return code {e.returncode}")
            raise
        
        # Execute CMake build
        print(f"CMake build: cmake --build . {' '.join(build_args)}")
        try:
            subprocess.run(
                ["cmake", "--build", "."] + build_args, 
                cwd=build_temp, 
                env=env,
                check=True
            )
            print("CMake build succeeded")
        except subprocess.CalledProcessError as e:
            print(f"CMake build failed with return code {e.returncode}")
            raise
        
        # Copy the built extension to the correct location
        print("Copying built extension...")
        if not self._copy_extension_to_target(build_temp, extdir):
            print("Warning: Could not find built extension, checking common locations...")
            # Check if extension was built in current directory (fallback)
            for pattern in ["pyminia*.so", "pyminia*.pyd", "pyminia*.dylib"]:
                for ext_file in Path(".").glob(pattern):
                    print(ext_file)
                    if ext_file.is_file():
                        target_file = extdir / ext_file.name
                        shutil.copy2(ext_file, target_file)
                        print(f"Copied extension from current dir: {ext_file} -> {target_file}")
                        # Clean up the file from current directory
                        ext_file.unlink()
                        break

# Read long description
def get_long_description():
    """Read README.md for long description"""
    try:
        with open("README.md", "r", encoding="utf-8") as fd:
            return fd.read()
    except FileNotFoundError:
        return "A C++ tool for feature transformation and hashing"


# Setup configuration
setup(
    name="pyminia",
    version="1.0.0",
    description="Python wrapper for minia, a C++ tool for feature transformation and hashing.",
    long_description=get_long_description(),
    long_description_content_type="text/markdown",
    license="AGPL-3.0",
    author="uopensail",
    author_email="timepi123@gmail.com",
    url="https://github.com/uopensail/minia",
    
    # Package configuration
    packages=find_packages(),
    py_modules=["minia"],
    ext_modules=[CMakeExtension("minia")],
    cmdclass={"build_ext": CMakeBuild},
    
    # Dependencies
    install_requires=get_requires("requirements.txt"),
    setup_requires=[
        "pybind11>=2.11.1",
    ],
    
    # Metadata
    keywords=[
        "feature transformation",
        "hashing",
        "machine learning",
        "data processing",
    ],
    
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Intended Audience :: Developers",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: GNU Affero General Public License v3",
        "Operating System :: OS Independent",
        "Programming Language :: C++",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Programming Language :: Python :: 3.12",
        "Programming Language :: Python :: 3.13",
        "Topic :: Scientific/Engineering :: Artificial Intelligence",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: Utilities",
    ],
    
    python_requires=">=3.7",
    
    # Include package data
    include_package_data=True,
    zip_safe=False,
)
