cmake_minimum_required(VERSION 3.12)
project(minia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall -fPIC")
SET(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_MACOSX_RPATH 1)

include(FetchContent)


FetchContent_Declare(
    antlr4
    GIT_REPOSITORY https://github.com/antlr/antlr4.git
    GIT_TAG        4.13.2  
    SOURCE_SUBDIR  runtime/Cpp  
)

set(ANTLR4_BUILD_SHARED ON CACHE BOOL "" FORCE)  
set(ANTLR4_WITH_STATIC_CRT OFF CACHE BOOL "" FORCE)
set(ANTLR4_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(antlr4)

include_directories(include)
include_directories(include/grammar)
include_directories(/usr/local/include)
include_directories(${antlr4_SOURCE_DIR}/runtime/Cpp/runtime/src)
link_directories(/usr/local/lib)

set(MINIA_SOURCES
    src/builtin.cc
    src/minia.cc
    src/MurmurHash3.cc
    src/grammar/minia.cc
    src/grammar/miniaBaseListener.cpp
    src/grammar/miniaLexer.cpp
    src/grammar/miniaListener.cpp
    src/grammar/miniaParser.cpp
)


add_library(minia_static STATIC ${MINIA_SOURCES})
target_link_libraries(minia_static PRIVATE
    antlr4_shared
    dl
    pthread
)



set_target_properties(minia_static PROPERTIES
BUILD_WITH_INSTALL_RPATH TRUE
INSTALL_RPATH "/usr/local/lib"
INSTALL_RPATH_USE_LINK_PATH TRUE
)

list(APPEND CMAKE_INSTALL_RPATH "/usr/local/lib")

option(PYBIND "Description of PYBIND" ON)
if (PYBIND)
    include(FetchContent)

    FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.11.1  # 指定稳定版本
    )

    FetchContent_MakeAvailable(pybind11)
    set (Python3_FIND_VIRTUALENV FIRST)
    set(PYTHON3_EXECUTABLE ${PYTHON_EXECUTABLE})

    find_package(Python3 COMPONENTS Interpreter Development)
    include_directories(${Python3_INCLUDE_DIRS})

    message(STATUS "PYTHON3_LIBRARIES = ${Python3_LIBRARIES}")
    message(STATUS "PYTHON3_EXECUTABLE = ${PYTHON_EXECUTABLE}")
    message(STATUS "PYTHON3_INCLUDE_DIRS = ${Python3_INCLUDE_DIRS}")


    # Include pybind11
    #find_package(pybind11 REQUIRED)
    include_directories(${PYTHON_INCLUDE_DIRS})

    # Define the Python module
    pybind11_add_module(minia      src/pyminia.cc)
    target_link_libraries(minia PRIVATE minia_static pthread)
endif()



