# Define a function to configure glog with both static and shared libraries
function(configure_glog)
    # Set glog version
    set(GLOG_VERSION "0.6.0")

    # Define download and installation directories
    set(GLOG_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/glog-download")
    set(GLOG_SOURCE_DIR "${GLOG_DOWNLOAD_DIR}/glog-${GLOG_VERSION}")
    set(GLOG_BUILD_DIR_STATIC "${CMAKE_BINARY_DIR}/glog-build-static")
    set(GLOG_BUILD_DIR_SHARED "${CMAKE_BINARY_DIR}/glog-build-shared")
    set(GLOG_INSTALL_DIR "${CMAKE_BINARY_DIR}/glog-install")

    # Create download, build and installation directories
    file(MAKE_DIRECTORY ${GLOG_DOWNLOAD_DIR})
    file(MAKE_DIRECTORY ${GLOG_BUILD_DIR_STATIC})
    file(MAKE_DIRECTORY ${GLOG_BUILD_DIR_SHARED})
    file(MAKE_DIRECTORY ${GLOG_INSTALL_DIR})

    # Define the path to the downloaded archive file
    set(GLOG_ARCHIVE "${GLOG_DOWNLOAD_DIR}/glog-${GLOG_VERSION}.tar.gz")
    set(GLOG_URL "https://github.com/google/glog/archive/v${GLOG_VERSION}.tar.gz")

    # Print the selected glog download URL
    message(STATUS "Selected glog URL: ${GLOG_URL}")

    # Check if the archive exists, download if it doesn't
    if(NOT EXISTS ${GLOG_ARCHIVE})
        message(STATUS "glog not found. Starting download...")
        message(STATUS "Downloading glog from ${GLOG_URL} to ${GLOG_ARCHIVE}...")
        file(DOWNLOAD ${GLOG_URL} ${GLOG_ARCHIVE} SHOW_PROGRESS)
        message(STATUS "glog archive successfully downloaded: ${GLOG_ARCHIVE}")
    else()
        message(STATUS "glog archive already exists: ${GLOG_ARCHIVE}")
    endif()

    # Check if the source directory exists, extract the archive if it doesn't
    if(NOT EXISTS ${GLOG_SOURCE_DIR})
        message(STATUS "Extracting glog archive to ${GLOG_DOWNLOAD_DIR}...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${GLOG_ARCHIVE}
            WORKING_DIRECTORY ${GLOG_DOWNLOAD_DIR}
            RESULT_VARIABLE TAR_RESULT
        )

        if(NOT TAR_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to extract glog archive. Error code: ${TAR_RESULT}")
        endif()

        message(STATUS "glog successfully extracted to ${GLOG_SOURCE_DIR}")
    else()
        message(STATUS "glog source is already extracted in ${GLOG_SOURCE_DIR}")
    endif()

    # Get gflags installation directory
    set(GFLAGS_INSTALL_DIR "${CMAKE_BINARY_DIR}/gflags-install")

    # Define library paths
    set(GLOG_STATIC_LIB "${GLOG_INSTALL_DIR}/lib/libglog.a")
    if(WIN32)
        set(GLOG_SHARED_LIB "${GLOG_INSTALL_DIR}/lib/glog.dll")
        set(GLOG_IMPORT_LIB "${GLOG_INSTALL_DIR}/lib/glog.lib")
    else()
        set(GLOG_SHARED_LIB "${GLOG_INSTALL_DIR}/lib/libglog${CMAKE_SHARED_LIBRARY_SUFFIX}")
    endif()

    # Check if both libraries exist
    set(NEED_BUILD FALSE)
    if(NOT EXISTS ${GLOG_STATIC_LIB})
        set(NEED_BUILD TRUE)
        message(STATUS "glog static library not found: ${GLOG_STATIC_LIB}")
    endif()
    
    if(NOT EXISTS ${GLOG_SHARED_LIB})
        set(NEED_BUILD TRUE)
        message(STATUS "glog shared library not found: ${GLOG_SHARED_LIB}")
    endif()

    if(NEED_BUILD)
        message(STATUS "Building glog with both static and shared libraries...")

        # ========================================
        # Build Static Library First
        # ========================================
        message(STATUS "🔧 Configuring glog static library...")
        execute_process(
            COMMAND ${CMAKE_COMMAND}
            -G "${CMAKE_GENERATOR}"
            -DCMAKE_INSTALL_PREFIX=${GLOG_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=Release
            -DCMAKE_CXX_STANDARD=17
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DBUILD_SHARED_LIBS=OFF
            -DBUILD_TESTING=OFF
            -DWITH_GFLAGS=ON
            -DWITH_UNWIND=OFF
            -DWITH_TLS=OFF
            -Dgflags_DIR=${GFLAGS_INSTALL_DIR}/lib/cmake/gflags
            ${GLOG_SOURCE_DIR}
            WORKING_DIRECTORY ${GLOG_BUILD_DIR_STATIC}
            RESULT_VARIABLE CONFIG_STATIC_RESULT
            OUTPUT_VARIABLE CONFIG_STATIC_OUTPUT
            ERROR_VARIABLE CONFIG_STATIC_ERROR
        )

        if(NOT CONFIG_STATIC_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to configure glog static build. Error code: ${CONFIG_STATIC_RESULT}\nOutput: ${CONFIG_STATIC_OUTPUT}\nError: ${CONFIG_STATIC_ERROR}")
        endif()

        message(STATUS "🔨 Building glog static library...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build . --config Release --parallel
            WORKING_DIRECTORY ${GLOG_BUILD_DIR_STATIC}
            RESULT_VARIABLE BUILD_STATIC_RESULT
            OUTPUT_VARIABLE BUILD_STATIC_OUTPUT
            ERROR_VARIABLE BUILD_STATIC_ERROR
        )

        if(NOT BUILD_STATIC_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to build glog static library. Error code: ${BUILD_STATIC_RESULT}\nOutput: ${BUILD_STATIC_OUTPUT}\nError: ${BUILD_STATIC_ERROR}")
        endif()

        message(STATUS "📦 Installing glog static library...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --install . --config Release
            WORKING_DIRECTORY ${GLOG_BUILD_DIR_STATIC}
            RESULT_VARIABLE INSTALL_STATIC_RESULT
            OUTPUT_VARIABLE INSTALL_STATIC_OUTPUT
            ERROR_VARIABLE INSTALL_STATIC_ERROR
        )

        if(NOT INSTALL_STATIC_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install glog static library. Error code: ${INSTALL_STATIC_RESULT}\nOutput: ${INSTALL_STATIC_OUTPUT}\nError: ${INSTALL_STATIC_ERROR}")
        endif()

        message(STATUS "✅ glog static library successfully built and installed")

        # ========================================
        # Build Shared Library Second
        # ========================================
        message(STATUS "🔧 Configuring glog shared library...")
        execute_process(
            COMMAND ${CMAKE_COMMAND}
            -G "${CMAKE_GENERATOR}"
            -DCMAKE_INSTALL_PREFIX=${GLOG_INSTALL_DIR}
            -DCMAKE_BUILD_TYPE=Release
            -DCMAKE_CXX_STANDARD=17
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DBUILD_SHARED_LIBS=ON
            -DBUILD_TESTING=OFF
            -DWITH_GFLAGS=ON
            -DWITH_UNWIND=OFF
            -DWITH_TLS=OFF
            -Dgflags_DIR=${GFLAGS_INSTALL_DIR}/lib/cmake/gflags
            ${GLOG_SOURCE_DIR}
            WORKING_DIRECTORY ${GLOG_BUILD_DIR_SHARED}
            RESULT_VARIABLE CONFIG_SHARED_RESULT
            OUTPUT_VARIABLE CONFIG_SHARED_OUTPUT
            ERROR_VARIABLE CONFIG_SHARED_ERROR
        )

        if(NOT CONFIG_SHARED_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to configure glog shared build. Error code: ${CONFIG_SHARED_RESULT}\nOutput: ${CONFIG_SHARED_OUTPUT}\nError: ${CONFIG_SHARED_ERROR}")
        endif()

        message(STATUS "🔨 Building glog shared library...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build . --config Release --parallel
            WORKING_DIRECTORY ${GLOG_BUILD_DIR_SHARED}
            RESULT_VARIABLE BUILD_SHARED_RESULT
            OUTPUT_VARIABLE BUILD_SHARED_OUTPUT
            ERROR_VARIABLE BUILD_SHARED_ERROR
        )

        if(NOT BUILD_SHARED_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to build glog shared library. Error code: ${BUILD_SHARED_RESULT}\nOutput: ${BUILD_SHARED_OUTPUT}\nError: ${BUILD_SHARED_ERROR}")
        endif()

        message(STATUS "📦 Installing glog shared library...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} --install . --config Release
            WORKING_DIRECTORY ${GLOG_BUILD_DIR_SHARED}
            RESULT_VARIABLE INSTALL_SHARED_RESULT
            OUTPUT_VARIABLE INSTALL_SHARED_OUTPUT
            ERROR_VARIABLE INSTALL_SHARED_ERROR
        )

        if(NOT INSTALL_SHARED_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install glog shared library. Error code: ${INSTALL_SHARED_RESULT}\nOutput: ${INSTALL_SHARED_OUTPUT}\nError: ${INSTALL_SHARED_ERROR}")
        endif()

        message(STATUS "✅ glog shared library successfully built and installed")

    else()
        message(STATUS "✅ Both glog static and shared libraries already exist")
    endif()

    # ========================================
    # Verify Installation
    # ========================================
    message(STATUS "🔍 Verifying glog installation...")
    
    # List all library files
    if(EXISTS ${GLOG_INSTALL_DIR}/lib)
        file(GLOB GLOG_LIBS "${GLOG_INSTALL_DIR}/lib/libglog*" "${GLOG_INSTALL_DIR}/lib/glog*")
        message(STATUS "📚 Found glog libraries:")
        foreach(lib ${GLOG_LIBS})
            get_filename_component(lib_name ${lib} NAME)
            file(SIZE ${lib} lib_size)
            math(EXPR lib_size_kb "${lib_size} / 1024")
            message(STATUS "  ✓ ${lib_name} (${lib_size_kb} KB)")
        endforeach()
    endif()

    # Verify specific libraries
    if(EXISTS ${GLOG_STATIC_LIB})
        file(SIZE ${GLOG_STATIC_LIB} static_size)
        math(EXPR static_size_kb "${static_size} / 1024")
        message(STATUS "✅ Static library verified: libglog.a (${static_size_kb} KB)")
    else()
        message(WARNING "❌ Static library not found: ${GLOG_STATIC_LIB}")
    endif()

    if(EXISTS ${GLOG_SHARED_LIB})
        file(SIZE ${GLOG_SHARED_LIB} shared_size)
        math(EXPR shared_size_kb "${shared_size} / 1024")
        get_filename_component(shared_name ${GLOG_SHARED_LIB} NAME)
        message(STATUS "✅ Shared library verified: ${shared_name} (${shared_size_kb} KB)")
    else()
        message(WARNING "❌ Shared library not found: ${GLOG_SHARED_LIB}")
    endif()

    # ========================================
    # Export Variables
    # ========================================
    set(GLOG_INCLUDE_DIR ${GLOG_INSTALL_DIR}/include CACHE PATH "glog include directory")
    set(GLOG_LIBRARY_DIR ${GLOG_INSTALL_DIR}/lib CACHE PATH "glog library directory")
    set(GLOG_STATIC_LIBRARY ${GLOG_STATIC_LIB} CACHE FILEPATH "glog static library")
    set(GLOG_SHARED_LIBRARY ${GLOG_SHARED_LIB} CACHE FILEPATH "glog shared library")
    
    # For backward compatibility
    set(GLOG_LIBRARY ${GLOG_SHARED_LIB} CACHE FILEPATH "glog library (default to shared)")

    # Export for Windows
    if(WIN32 AND EXISTS ${GLOG_IMPORT_LIB})
        set(GLOG_IMPORT_LIBRARY ${GLOG_IMPORT_LIB} CACHE FILEPATH "glog import library")
    endif()

    # Print summary
    message(STATUS "🎉 glog configuration completed!")
    message(STATUS "📁 Installation directory: ${GLOG_INSTALL_DIR}")
    message(STATUS "📂 Include directory: ${GLOG_INCLUDE_DIR}")
    message(STATUS "📚 Library directory: ${GLOG_LIBRARY_DIR}")
    message(STATUS "🔗 Static library: ${GLOG_STATIC_LIBRARY}")
    message(STATUS "🔗 Shared library: ${GLOG_SHARED_LIBRARY}")

endfunction()
