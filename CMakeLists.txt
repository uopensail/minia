# ==============================================================================
# Minia Project Configuration
# ==============================================================================

cmake_minimum_required(VERSION 3.16)
project(minia 
    VERSION 1.0.0 
    LANGUAGES CXX
    DESCRIPTION "Minia library for advanced data processing"
)

# ==============================================================================
# Project Options
# ==============================================================================

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(BUILD_STATIC_LIBS "Build static libraries" ON)
option(BUILD_SHARED_C_LIBS "Build shared C libraries" ON)
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)
option(BUILD_TESTS "Build unit tests" OFF)
option(BUILD_EXAMPLES "Build example programs" OFF)

# ==============================================================================
# C++ Standard and Compiler Settings
# ==============================================================================

# Set C++ standard requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Compiler-specific configuration
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    # Common compiler flags
    add_compile_options(-fPIC -Wall -Wextra -Wpedantic)
    add_compile_definitions(__GCC__)
    
    # Debug configuration
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb -DDEBUG")
    
    # Release configuration
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
    
    # Additional optimizations for release
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")
endif()

# ==============================================================================
# Platform-Specific Settings
# ==============================================================================

if(APPLE)
    # macOS specific settings
    add_compile_definitions(_LIBCPP_DISABLE_AVAILABILITY)
    set(CMAKE_MACOSX_RPATH ON)
    set(SHARED_LIB_EXT ".dylib")
    
    message(STATUS "Configuring for macOS platform")
elseif(UNIX)
    # Linux specific settings
    set(SHARED_LIB_EXT ".so")
    
    message(STATUS "Configuring for Linux platform")
elseif(WIN32)
    # Windows specific settings
    set(SHARED_LIB_EXT ".dll")
    add_compile_definitions(_WIN32_WINNT=0x0601)
    
    message(STATUS "Configuring for Windows platform")
endif()

# ==============================================================================
# Third-Party Dependencies
# ==============================================================================

message(STATUS "Configuring third-party dependencies...")

# Include dependency configuration files
include(cmake/antlr4.cmake)
include(cmake/flatbuffers.cmake)
include(cmake/gflags.cmake)
include(cmake/glog.cmake)

# Configure all dependencies
configure_antlr4_runtime()
configure_flatbuffers()
configure_gflags()
configure_glog()

# System dependencies
find_package(Threads REQUIRED)

message(STATUS "Third-party dependencies configured successfully")

# ==============================================================================
# Source Files Configuration
# ==============================================================================

# Define core source files
set(MINIA_CORE_SOURCES
    src/common.cc
    src/builtin.cc
    src/minia.cc
    src/MurmurHash3.cc
)

# Define grammar-generated source files
set(MINIA_GRAMMAR_SOURCES
    src/grammar/minia.cc
    src/grammar/miniaBaseListener.cpp
    src/grammar/miniaLexer.cpp
    src/grammar/miniaListener.cpp
    src/grammar/miniaParser.cpp
)

# Combine all source files
set(MINIA_SOURCES
    ${MINIA_CORE_SOURCES}
    ${MINIA_GRAMMAR_SOURCES}
)

# ==============================================================================
# Common Target Configuration Function
# ==============================================================================

function(configure_minia_target target_name)
    # Set include directories
    target_include_directories(${target_name}
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/grammar>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${ANTLR4_INCLUDE_DIR}
            ${FLATBUFFERS_INCLUDE_DIR}
            ${GFLAGS_INCLUDE_DIR}
            ${GLOG_INCLUDE_DIR}
    )

    # Set library search paths
    target_link_directories(${target_name} PRIVATE
        ${ANTLR4_LIBRARY_DIR}
        ${FLATBUFFERS_LIBRARY_DIR}
        ${GFLAGS_LIBRARY_DIR}
        ${GLOG_LIBRARY_DIR}
    )

    # Set common properties
    set_target_properties(${target_name} PROPERTIES
        POSITION_INDEPENDENT_CODE ON
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
endfunction()

# ==============================================================================
# Shared Library Target
# ==============================================================================

if(BUILD_SHARED_LIBS)
    message(STATUS "Configuring shared library target...")
    
    add_library(minia_shared SHARED ${MINIA_SOURCES})
    configure_minia_target(minia_shared)

    # Set shared library specific properties
    set_target_properties(minia_shared PROPERTIES
        OUTPUT_NAME minia
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
    )

    # Link shared dependencies
    target_link_libraries(minia_shared
        PRIVATE
            antlr4-runtime
            flatbuffers
            gflags
            glog
            Threads::Threads
            ${CMAKE_DL_LIBS}
    )

    # Configure RPATH for shared library
    if(CMAKE_SYSTEM_NAME MATCHES "Linux|Darwin")
        set_target_properties(minia_shared PROPERTIES
            BUILD_WITH_INSTALL_RPATH OFF
            BUILD_RPATH_USE_ORIGIN ON
            INSTALL_RPATH_USE_LINK_PATH ON
        )

        if(APPLE)
            set_target_properties(minia_shared PROPERTIES
                INSTALL_RPATH "@loader_path/../lib;@loader_path;/usr/local/lib"
            )
        else()
            set_target_properties(minia_shared PROPERTIES
                INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN:/usr/local/lib"
            )
        endif()
    endif()
    
    message(STATUS "Shared library target configured successfully")
endif()

# ==============================================================================
# Static Library Target
# ==============================================================================

if(BUILD_STATIC_LIBS)
    message(STATUS "Configuring static library target...")
    
    add_library(minia_static STATIC ${MINIA_SOURCES})
    configure_minia_target(minia_static)

    # Set static library specific properties
    set_target_properties(minia_static PROPERTIES
        OUTPUT_NAME minia_static
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    )

    # Link static dependencies
    target_link_libraries(minia_static PRIVATE
        ${ANTLR4_LIBRARY_DIR}/libantlr4-runtime.a
        ${FLATBUFFERS_LIBRARY_DIR}/libflatbuffers.a
        ${GFLAGS_LIBRARY_DIR}/libgflags.a
        ${GLOG_LIBRARY_DIR}/libglog.a
        Threads::Threads
        ${CMAKE_DL_LIBS}
    )
    
    message(STATUS "Static library target configured successfully")
endif()

# ==============================================================================
# C Interface Shared Library
# ==============================================================================

if(BUILD_SHARED_C_LIBS)
    message(STATUS "Configuring C interface shared library...")
    
    add_library(cminia_shared SHARED ${MINIA_SOURCES} src/cminia.cc)
    configure_minia_target(cminia_shared)

    # Set C library specific properties
    set_target_properties(cminia_shared PROPERTIES
        OUTPUT_NAME cminia
        C_STANDARD 99
        C_STANDARD_REQUIRED ON
    )

    # Link dependencies for C interface
    target_link_libraries(cminia_shared PRIVATE
        ${ANTLR4_LIBRARY_DIR}/libantlr4-runtime.a
        ${FLATBUFFERS_LIBRARY_DIR}/libflatbuffers.a
        ${GFLAGS_LIBRARY_DIR}/libgflags.a
        ${GLOG_LIBRARY_DIR}/libglog.a
        Threads::Threads
        ${CMAKE_DL_LIBS}
    )
    
    message(STATUS "C interface shared library configured successfully")
endif()

# ==============================================================================
# Python Bindings
# ==============================================================================

if(BUILD_PYTHON_BINDINGS)
    message(STATUS "Configuring Python bindings...")
    
    # Configure pybind11
    include(cmake/pybind11.cmake)
    configure_pybind11()
    
    # Create Python module
    pybind11_add_module(pyminia src/pyminia.cc)
    configure_minia_target(pyminia)

    # Link Python module dependencies
    if(BUILD_STATIC_LIBS)
        target_link_libraries(pyminia PRIVATE minia_static)
    else()
        target_link_libraries(pyminia PRIVATE
            ${ANTLR4_LIBRARY_DIR}/libantlr4-runtime.a
            ${FLATBUFFERS_LIBRARY_DIR}/libflatbuffers.a
            ${GFLAGS_LIBRARY_DIR}/libgflags.a
            ${GLOG_LIBRARY_DIR}/libglog.a
            Threads::Threads
            ${CMAKE_DL_LIBS}
        )
    endif()

    # Set Python module properties
    set_target_properties(pyminia PROPERTIES
        OUTPUT_NAME pyminia
        SUFFIX "${PYTHON_MODULE_EXTENSION}"
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python
    )
    
    message(STATUS "Python bindings configured successfully")
endif()

# ==============================================================================
# Installation Configuration
# ==============================================================================

include(GNUInstallDirs)

# Determine which targets to install
set(INSTALL_TARGETS)
if(BUILD_SHARED_LIBS)
    list(APPEND INSTALL_TARGETS minia_shared)
endif()
if(BUILD_STATIC_LIBS)
    list(APPEND INSTALL_TARGETS minia_static)
endif()
if(BUILD_SHARED_C_LIBS)
    list(APPEND INSTALL_TARGETS cminia_shared)
endif()

# ==============================================================================
# Build Summary
# ==============================================================================

message(STATUS "")
message(STATUS "=== Minia Build Configuration Summary ===")
message(STATUS "Project Version:      ${PROJECT_VERSION}")
message(STATUS "Build Type:           ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard:         C++${CMAKE_CXX_STANDARD}")
message(STATUS "")
message(STATUS "Build Options:")
message(STATUS "  Shared Libraries:   ${BUILD_SHARED_LIBS}")
message(STATUS "  Static Libraries:   ${BUILD_STATIC_LIBS}")
message(STATUS "  C Interface:        ${BUILD_SHARED_C_LIBS}")
message(STATUS "  Python Bindings:    ${BUILD_PYTHON_BINDINGS}")
message(STATUS "  Unit Tests:         ${BUILD_TESTS}")
message(STATUS "  Examples:           ${BUILD_EXAMPLES}")
message(STATUS "")
message(STATUS "Installation Prefix:  ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Library Directory:    ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "Include Directory:    ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "")
message(STATUS "Compiler Information:")
message(STATUS "  Compiler ID:        ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  Compiler Version:   ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Compiler Path:      ${CMAKE_CXX_COMPILER}")
message(STATUS "==========================================")
message(STATUS "")
