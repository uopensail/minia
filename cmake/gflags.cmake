# Define a function to configure gflags
function(configure_gflags)
    # Set gflags version
    set(GFLAGS_VERSION "2.2.2")
    
    # Define download and installation directories
    set(GFLAGS_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/gflags-download")
    set(GFLAGS_SOURCE_DIR "${GFLAGS_DOWNLOAD_DIR}/gflags-${GFLAGS_VERSION}")
    set(GFLAGS_BUILD_DIR "${CMAKE_BINARY_DIR}/gflags-build")
    set(GFLAGS_INSTALL_DIR "${CMAKE_BINARY_DIR}/gflags-install")
    
    # Create download, build and installation directories
    file(MAKE_DIRECTORY ${GFLAGS_DOWNLOAD_DIR})
    file(MAKE_DIRECTORY ${GFLAGS_BUILD_DIR})
    file(MAKE_DIRECTORY ${GFLAGS_INSTALL_DIR})
    
    # Define the path to the downloaded archive file
    set(GFLAGS_ARCHIVE "${GFLAGS_DOWNLOAD_DIR}/gflags-${GFLAGS_VERSION}.tar.gz")
    set(GFLAGS_URL "https://github.com/gflags/gflags/archive/v${GFLAGS_VERSION}.tar.gz")
    
    # Print the selected gflags download URL
    message(STATUS "Selected gflags URL: ${GFLAGS_URL}")
    
    # Check if the archive exists, download if it doesn't
    if(NOT EXISTS ${GFLAGS_ARCHIVE})
        message(STATUS "gflags not found. Starting download...")
        message(STATUS "Downloading gflags from ${GFLAGS_URL} to ${GFLAGS_ARCHIVE}...")
        file(DOWNLOAD ${GFLAGS_URL} ${GFLAGS_ARCHIVE} SHOW_PROGRESS)
        message(STATUS "gflags archive successfully downloaded: ${GFLAGS_ARCHIVE}")
    else()
        message(STATUS "gflags archive already exists: ${GFLAGS_ARCHIVE}")
    endif()
    
    # Check if the source directory exists, extract the archive if it doesn't
    if(NOT EXISTS ${GFLAGS_SOURCE_DIR})
        message(STATUS "Extracting gflags archive to ${GFLAGS_DOWNLOAD_DIR}...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${GFLAGS_ARCHIVE}
            WORKING_DIRECTORY ${GFLAGS_DOWNLOAD_DIR}
            RESULT_VARIABLE TAR_RESULT
        )
        if(NOT TAR_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to extract gflags archive. Error code: ${TAR_RESULT}")
        endif()
        message(STATUS "gflags successfully extracted to ${GFLAGS_SOURCE_DIR}")
    else()
        message(STATUS "gflags source is already extracted in ${GFLAGS_SOURCE_DIR}")
    endif()
    
    # Check if the installation directory exists, build and install gflags if it doesn't
    if(NOT EXISTS ${GFLAGS_INSTALL_DIR}/lib/libgflags${CMAKE_SHARED_LIBRARY_SUFFIX})
        message(STATUS "Building and installing gflags...")
        
        # Configure gflags build
        execute_process(
            COMMAND ${CMAKE_COMMAND} 
                -G "${CMAKE_GENERATOR}"
                -DCMAKE_INSTALL_PREFIX=${GFLAGS_INSTALL_DIR}
                -DCMAKE_BUILD_TYPE=Release
                -DCMAKE_CXX_STANDARD=17
                -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                -DBUILD_SHARED_LIBS=ON
                -DBUILD_STATIC_LIBS=ON
                -DBUILD_TESTING=OFF
                -DBUILD_gflags_LIB=ON
                -DINSTALL_HEADERS=ON
                ${GFLAGS_SOURCE_DIR}
            WORKING_DIRECTORY ${GFLAGS_BUILD_DIR}
            RESULT_VARIABLE CONFIG_RESULT
        )
        if(NOT CONFIG_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to configure gflags build. Error code: ${CONFIG_RESULT}")
        endif()
        
        # Build gflags
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build . --config Release
            WORKING_DIRECTORY ${GFLAGS_BUILD_DIR}
            RESULT_VARIABLE BUILD_RESULT
        )
        if(NOT BUILD_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to build gflags. Error code: ${BUILD_RESULT}")
        endif()
        
        # Install gflags
        execute_process(
            COMMAND ${CMAKE_COMMAND} --install . --config Release
            WORKING_DIRECTORY ${GFLAGS_BUILD_DIR}
            RESULT_VARIABLE INSTALL_RESULT
        )
        if(NOT INSTALL_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install gflags. Error code: ${INSTALL_RESULT}")
        endif()
        
        message(STATUS "gflags successfully built and installed to ${GFLAGS_INSTALL_DIR}")
    else()
        message(STATUS "gflags is already installed in ${GFLAGS_INSTALL_DIR}")
    endif()
    
    # Export installation path as cache variables for use elsewhere
    set(GFLAGS_INCLUDE_DIR ${GFLAGS_INSTALL_DIR}/include CACHE PATH "gflags include directory")
    set(GFLAGS_LIBRARY_DIR ${GFLAGS_INSTALL_DIR}/lib CACHE PATH "gflags library directory")
    set(GFLAGS_LIBRARY ${GFLAGS_INSTALL_DIR}/lib/libgflags${CMAKE_SHARED_LIBRARY_SUFFIX} CACHE FILEPATH "gflags library")
    
    # Print configured installation directory
    message(STATUS "Configured gflags installation directory: ${GFLAGS_INSTALL_DIR}")
    message(STATUS "gflags include directory: ${GFLAGS_INCLUDE_DIR}")
    message(STATUS "gflags library: ${GFLAGS_LIBRARY}")
endfunction()
