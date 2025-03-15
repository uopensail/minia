cmake_minimum_required(VERSION 3.12)
project(minia)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall -fPIC")
SET(CMAKE_CXX_FLAGS "-std=c++17")
set(CMAKE_MACOSX_RPATH 1)

include_directories(include)
include_directories(include/grammar)
include_directories(/usr/local/include)
include_directories(/usr/local/include/antlr4-runtime)
link_directories(/usr/local/lib)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 REQUIRED)

set(MINIA_SOURCES
    src/builtin.cc
    src/minia.cc
    src/MurmurHash3.cc
    src/pyminia.cc
    src/grammar/minia.cc
    src/grammar/miniaBaseListener.cpp
    src/grammar/miniaLexer.cpp
    src/grammar/miniaListener.cpp
    src/grammar/miniaParser.cpp
)

pybind11_add_module(minia ${MINIA_SOURCES})

target_include_directories(minia PRIVATE
    include
    ${Python3_INCLUDE_DIRS}
)

target_link_libraries(minia PRIVATE
    antlr4-runtime
    Python3::Python
    pybind11::module
    dl
    pthread
)

set_target_properties(minia PROPERTIES
BUILD_WITH_INSTALL_RPATH TRUE
INSTALL_RPATH "/usr/local/lib"
INSTALL_RPATH_USE_LINK_PATH TRUE
)

list(APPEND CMAKE_INSTALL_RPATH "/usr/local/lib")

