cmake_minimum_required(VERSION 3.16)
project(minia VERSION 1.0.0 LANGUAGES CXX)

# Set the C/CXX standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set compilation options
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific settings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fPIC -Wall)
    add_compile_definitions(__GCC__)
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -ggdb")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif()

# Platform-specific settings
if(APPLE)
    add_compile_definitions(_LIBCPP_DISABLE_AVAILABILITY)
    set(CMAKE_MACOSX_RPATH ON)
    set(SHARED_LIB_EXT ".dylib")
else()
    set(SHARED_LIB_EXT ".so")
endif()

# Set up a dynamic library build
set(BUILD_SHARED_LIBS ON)

# Include and configure all dependencies
include(cmake/antlr4.cmake)
include(cmake/flatbuffers.cmake)
include(cmake/gflags.cmake)
include(cmake/glog.cmake)
include(cmake/pybind11.cmake)

configure_antlr4_runtime()
configure_flatbuffers()
configure_gflags()
configure_glog()

# Find the system library
find_package(Threads REQUIRED)

# Source files
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

# The main dynamic library
add_library(minia_shared SHARED ${MINIA_SOURCES})

# Set the inclusion directory
target_include_directories(minia_shared
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

# Set the library search path
target_link_directories(minia_shared PRIVATE
    ${ANTLR4_LIBRARY_DIR}
    ${FLATBUFFERS_LIBRARY_DIR}
    ${GFLAGS_LIBRARY_DIR}
    ${GLOG_LIBRARY_DIR}
)

# Set dynamic library properties
set_target_properties(minia_shared PROPERTIES
    OUTPUT_NAME minia
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    POSITION_INDEPENDENT_CODE ON
)

# Link dependencies
target_link_libraries(minia_shared
    PRIVATE
    antlr4-runtime
    flatbuffers
    gflags
    glog
    Threads::Threads
    ${CMAKE_DL_LIBS}
)

# Handle RPATH
if(CMAKE_SYSTEM_NAME MATCHES "Linux|Darwin")
    set_target_properties(minia_shared PROPERTIES
        BUILD_WITH_INSTALL_RPATH OFF
        BUILD_RPATH_USE_ORIGIN ON
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

    set_target_properties(minia_shared PROPERTIES
        INSTALL_RPATH_USE_LINK_PATH ON
    )
endif()

# Optional static library
option(BUILD_STATIC_LIBS "Build static libraries" ON)

if(BUILD_STATIC_LIBS)
    add_library(minia_static STATIC ${MINIA_SOURCES})

    target_include_directories(minia_static
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

    target_link_directories(minia_static PRIVATE
        ${ANTLR4_LIBRARY_DIR}
        ${FLATBUFFERS_LIBRARY_DIR}
        ${GFLAGS_LIBRARY_DIR}
        ${GLOG_LIBRARY_DIR}
    )

    target_link_libraries(minia_static PRIVATE
        ${ANTLR4_LIBRARY_DIR}/libantlr4-runtime.a
        ${FLATBUFFERS_LIBRARY_DIR}/libflatbuffers.a
        ${GFLAGS_LIBRARY_DIR}/libgflags.a
        ${GLOG_LIBRARY_DIR}/libglog.a
        Threads::Threads
        ${CMAKE_DL_LIBS}
    )

    set_target_properties(minia_static PROPERTIES
        OUTPUT_NAME minia_static
        POSITION_INDEPENDENT_CODE ON
    )
endif()

# Python bindings
option(BUILD_PYTHON_BINDINGS "Build Python bindings" ON)

if(BUILD_PYTHON_BINDINGS)
    configure_pybind11()

    pybind11_add_module(minia src/pyminia.cc)

    target_include_directories(minia
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

    target_link_libraries(minia PRIVATE
        minia_static
        ${ANTLR4_LIBRARY_DIR}/libantlr4-runtime.a
        ${FLATBUFFERS_LIBRARY_DIR}/libflatbuffers.a
        ${GFLAGS_LIBRARY_DIR}/libgflags.a
        ${GLOG_LIBRARY_DIR}/libglog.a
        Threads::Threads
        ${CMAKE_DL_LIBS}
    )

    set_target_properties(minia PROPERTIES
        OUTPUT_NAME minia
        SUFFIX "${PYTHON_MODULE_EXTENSION}"
    )
endif()

# Installation rules
include(GNUInstallDirs)

if(BUILD_STATIC_LIBS)
    install(TARGETS minia_shared minia_static
        EXPORT miniaTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
else()
    install(TARGETS minia_shared
        EXPORT miniaTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h" PATTERN "*.hpp"
)

install(EXPORT miniaTargets
    FILE miniaTargets.cmake
    NAMESPACE minia::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/minia
)


# Print the configuration information
message(STATUS "=== Minia Build Configuration ===")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build shared libs: ON")
message(STATUS "Build static libs: ${BUILD_STATIC_LIBS}")
message(STATUS "Python bindings: ${BUILD_PYTHON_BINDINGS}")
message(STATUS "Tests: ${BUILD_TESTS}")
message(STATUS "Examples: ${BUILD_EXAMPLES}")
message(STATUS "================================")
