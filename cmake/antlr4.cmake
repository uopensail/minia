# Define a function to configure ANTLR4 Runtime
function(configure_antlr4_runtime)
    # Set ANTLR4 Runtime version
    set(ANTLR4_VERSION "4.13.2")
    
    # Define download and installation directories
    set(ANTLR4_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/antlr4-download")
    set(ANTLR4_SOURCE_DIR "${ANTLR4_DOWNLOAD_DIR}/antlr4-cpp-runtime-${ANTLR4_VERSION}-source")
    set(ANTLR4_BUILD_DIR "${CMAKE_BINARY_DIR}/antlr4-build")
    set(ANTLR4_INSTALL_DIR "${CMAKE_BINARY_DIR}/antlr4-install")
    
    # Create download, build and installation directories
    file(MAKE_DIRECTORY ${ANTLR4_DOWNLOAD_DIR})
    file(MAKE_DIRECTORY ${ANTLR4_BUILD_DIR})
    file(MAKE_DIRECTORY ${ANTLR4_INSTALL_DIR})
    
    # Define the path to the downloaded archive file
    set(ANTLR4_ARCHIVE "${ANTLR4_DOWNLOAD_DIR}/antlr4-cpp-runtime-${ANTLR4_VERSION}-source.zip")
    set(ANTLR4_URL "https://www.antlr.org/download/antlr4-cpp-runtime-${ANTLR4_VERSION}-source.zip")
    
    # Print the selected ANTLR4 Runtime download URL
    message(STATUS "Selected ANTLR4 Runtime URL: ${ANTLR4_URL}")
    
    # Check if the archive exists, download if it doesn't
    if(NOT EXISTS ${ANTLR4_ARCHIVE})
        message(STATUS "ANTLR4 Runtime not found. Starting download...")
        message(STATUS "Downloading ANTLR4 Runtime from ${ANTLR4_URL} to ${ANTLR4_ARCHIVE}...")
        file(DOWNLOAD ${ANTLR4_URL} ${ANTLR4_ARCHIVE} SHOW_PROGRESS)
        message(STATUS "ANTLR4 Runtime archive successfully downloaded: ${ANTLR4_ARCHIVE}")
    else()
        message(STATUS "ANTLR4 Runtime archive already exists: ${ANTLR4_ARCHIVE}")
    endif()
    
    # Check if the source directory exists, extract the archive if it doesn't
    if(NOT EXISTS ${ANTLR4_SOURCE_DIR})
        message(STATUS "Extracting ANTLR4 Runtime archive to ${ANTLR4_SOURCE_DIR}...")
        file(MAKE_DIRECTORY ${ANTLR4_SOURCE_DIR})
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xf ${ANTLR4_ARCHIVE}
            WORKING_DIRECTORY ${ANTLR4_SOURCE_DIR}
            RESULT_VARIABLE TAR_RESULT
        )
        if(NOT TAR_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to extract ANTLR4 Runtime archive. Error code: ${TAR_RESULT}")
        endif()
        message(STATUS "ANTLR4 Runtime successfully extracted to ${ANTLR4_SOURCE_DIR}")
    else()
        message(STATUS "ANTLR4 Runtime source is already extracted in ${ANTLR4_SOURCE_DIR}")
    endif()
    
    # Determine the shared library suffix based on the platform
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(ANTLR4_SHARED_LIB "${ANTLR4_INSTALL_DIR}/lib/libantlr4-runtime.dylib")
    else()
        set(ANTLR4_SHARED_LIB "${ANTLR4_INSTALL_DIR}/lib/libantlr4-runtime.so")
    endif()
    
    # Check if the installation directory exists, build and install ANTLR4 Runtime if it doesn't
    if(NOT EXISTS ${ANTLR4_SHARED_LIB})
        message(STATUS "Building and installing ANTLR4 Runtime...")
        
        # Configure ANTLR4 Runtime build
        execute_process(
            COMMAND ${CMAKE_COMMAND}
                -G "${CMAKE_GENERATOR}"
                -DCMAKE_INSTALL_PREFIX=${ANTLR4_INSTALL_DIR}
                -DCMAKE_BUILD_TYPE=Release
                -DCMAKE_CXX_STANDARD=17
                -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                -DBUILD_SHARED_LIBS=ON
                -DANTLR4_INSTALL=ON
                -DANTLR_BUILD_CPP_TESTS=OFF
                ${ANTLR4_SOURCE_DIR}
            WORKING_DIRECTORY ${ANTLR4_BUILD_DIR}
            RESULT_VARIABLE CONFIG_RESULT
        )
        if(NOT CONFIG_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to configure ANTLR4 Runtime build. Error code: ${CONFIG_RESULT}")
        endif()
        
        # Build ANTLR4 Runtime
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build . --config Release
            WORKING_DIRECTORY ${ANTLR4_BUILD_DIR}
            RESULT_VARIABLE BUILD_RESULT
        )
        if(NOT BUILD_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to build ANTLR4 Runtime. Error code: ${BUILD_RESULT}")
        endif()
        
        # Install ANTLR4 Runtime
        execute_process(
            COMMAND ${CMAKE_COMMAND} --install . --config Release
            WORKING_DIRECTORY ${ANTLR4_BUILD_DIR}
            RESULT_VARIABLE INSTALL_RESULT
        )
        if(NOT INSTALL_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install ANTLR4 Runtime. Error code: ${INSTALL_RESULT}")
        endif()
        
        message(STATUS "ANTLR4 Runtime successfully built and installed to ${ANTLR4_INSTALL_DIR}")
    else()
        message(STATUS "ANTLR4 Runtime is already installed in ${ANTLR4_INSTALL_DIR}")
    endif()
    
    # Export installation path as cache variables for use elsewhere
    set(ANTLR4_INCLUDE_DIR ${ANTLR4_INSTALL_DIR}/include/antlr4-runtime CACHE PATH "ANTLR4 Runtime include directory")
    set(ANTLR4_LIBRARY_DIR ${ANTLR4_INSTALL_DIR}/lib CACHE PATH "ANTLR4 Runtime library directory")
    
    # Set library file path (based on operating system)
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(ANTLR4_LIBRARY ${ANTLR4_INSTALL_DIR}/lib/libantlr4-runtime.dylib CACHE FILEPATH "ANTLR4 Runtime library")
    else()
        set(ANTLR4_LIBRARY ${ANTLR4_INSTALL_DIR}/lib/libantlr4-runtime.so CACHE FILEPATH "ANTLR4 Runtime library")
    endif()
    
    # Print configured installation directory
    message(STATUS "Configured ANTLR4 Runtime installation directory: ${ANTLR4_INSTALL_DIR}")
    message(STATUS "ANTLR4 Runtime include directory: ${ANTLR4_INCLUDE_DIR}")
    message(STATUS "ANTLR4 Runtime library: ${ANTLR4_LIBRARY}")
endfunction()
