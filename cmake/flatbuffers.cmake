# Define a function to configure FlatBuffers
function(configure_flatbuffers)
    # Set FlatBuffers version
    set(FLATBUFFERS_VERSION "25.2.10")
    
    # Define download and installation directories
    set(FLATBUFFERS_DOWNLOAD_DIR "${CMAKE_BINARY_DIR}/flatbuffers-download")
    set(FLATBUFFERS_SOURCE_DIR "${FLATBUFFERS_DOWNLOAD_DIR}/flatbuffers-${FLATBUFFERS_VERSION}")
    set(FLATBUFFERS_BUILD_DIR "${CMAKE_BINARY_DIR}/flatbuffers-build")
    set(FLATBUFFERS_INSTALL_DIR "${CMAKE_BINARY_DIR}/flatbuffers-install")
    
    # Create download, build and installation directories
    file(MAKE_DIRECTORY ${FLATBUFFERS_DOWNLOAD_DIR})
    file(MAKE_DIRECTORY ${FLATBUFFERS_BUILD_DIR})
    file(MAKE_DIRECTORY ${FLATBUFFERS_INSTALL_DIR})
    
    # Define the path to the downloaded archive file
    set(FLATBUFFERS_ARCHIVE "${FLATBUFFERS_DOWNLOAD_DIR}/flatbuffers-${FLATBUFFERS_VERSION}.tar.gz")
    set(FLATBUFFERS_URL "https://github.com/google/flatbuffers/archive/v${FLATBUFFERS_VERSION}.tar.gz")
    
    # Print the selected FlatBuffers download URL
    message(STATUS "Selected FlatBuffers URL: ${FLATBUFFERS_URL}")
    
    # Check if the archive exists, download if it doesn't
    if(NOT EXISTS ${FLATBUFFERS_ARCHIVE})
        message(STATUS "FlatBuffers not found. Starting download...")
        message(STATUS "Downloading FlatBuffers from ${FLATBUFFERS_URL} to ${FLATBUFFERS_ARCHIVE}...")
        file(DOWNLOAD ${FLATBUFFERS_URL} ${FLATBUFFERS_ARCHIVE} SHOW_PROGRESS)
        message(STATUS "FlatBuffers archive successfully downloaded: ${FLATBUFFERS_ARCHIVE}")
    else()
        message(STATUS "FlatBuffers archive already exists: ${FLATBUFFERS_ARCHIVE}")
    endif()
    
    # Check if the source directory exists, extract the archive if it doesn't
    if(NOT EXISTS ${FLATBUFFERS_SOURCE_DIR})
        message(STATUS "Extracting FlatBuffers archive to ${FLATBUFFERS_DOWNLOAD_DIR}...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xzf ${FLATBUFFERS_ARCHIVE}
            WORKING_DIRECTORY ${FLATBUFFERS_DOWNLOAD_DIR}
            RESULT_VARIABLE TAR_RESULT
        )
        if(NOT TAR_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to extract FlatBuffers archive. Error code: ${TAR_RESULT}")
        endif()
        message(STATUS "FlatBuffers successfully extracted to ${FLATBUFFERS_SOURCE_DIR}")
    else()
        message(STATUS "FlatBuffers source is already extracted in ${FLATBUFFERS_SOURCE_DIR}")
    endif()
    
    # Check if FlatBuffers needs to be built and installed
    # Note: On macOS, the shared library extension is .dylib, on Linux it's .so
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(FLATBUFFERS_SHARED_LIB "${FLATBUFFERS_INSTALL_DIR}/lib/libflatbuffers.dylib")
    else()
        set(FLATBUFFERS_SHARED_LIB "${FLATBUFFERS_INSTALL_DIR}/lib/libflatbuffers.so")
    endif()
    
    if(NOT EXISTS ${FLATBUFFERS_SHARED_LIB})
        message(STATUS "Building and installing FlatBuffers...")
        
        # Configure FlatBuffers build
        execute_process(
            COMMAND ${CMAKE_COMMAND} 
                -G "${CMAKE_GENERATOR}"
                -DCMAKE_INSTALL_PREFIX=${FLATBUFFERS_INSTALL_DIR}
                -DCMAKE_BUILD_TYPE=Release
                -DCMAKE_CXX_STANDARD=17
                -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                -DFLATBUFFERS_BUILD_TESTS=OFF
                -DFLATBUFFERS_BUILD_FLATLIB=ON
                -DFLATBUFFERS_BUILD_FLATC=OFF
                -DFLATBUFFERS_BUILD_FLATHASH=OFF
                -DFLATBUFFERS_INSTALL=ON
                -DBUILD_SHARED_LIBS=ON
                ${FLATBUFFERS_SOURCE_DIR}
            WORKING_DIRECTORY ${FLATBUFFERS_BUILD_DIR}
            RESULT_VARIABLE CONFIG_RESULT
        )
        if(NOT CONFIG_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to configure FlatBuffers build. Error code: ${CONFIG_RESULT}")
        endif()
        
        # Build FlatBuffers
        execute_process(
            COMMAND ${CMAKE_COMMAND} --build . --config Release
            WORKING_DIRECTORY ${FLATBUFFERS_BUILD_DIR}
            RESULT_VARIABLE BUILD_RESULT
        )
        if(NOT BUILD_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to build FlatBuffers. Error code: ${BUILD_RESULT}")
        endif()
        
        # Install FlatBuffers
        execute_process(
            COMMAND ${CMAKE_COMMAND} --install . --config Release
            WORKING_DIRECTORY ${FLATBUFFERS_BUILD_DIR}
            RESULT_VARIABLE INSTALL_RESULT
        )
        if(NOT INSTALL_RESULT EQUAL 0)
            message(FATAL_ERROR "Failed to install FlatBuffers. Error code: ${INSTALL_RESULT}")
        endif()
        
        # Check if the library file exists
        if(NOT EXISTS ${FLATBUFFERS_SHARED_LIB})
            # Try to find the actual library files
            file(GLOB FLATBUFFERS_LIB_FILES "${FLATBUFFERS_INSTALL_DIR}/lib/libflatbuffers*")
            message(STATUS "FlatBuffers library files found: ${FLATBUFFERS_LIB_FILES}")
            
            # If library files are found but the name doesn't match expectations, create a symbolic link
            if(FLATBUFFERS_LIB_FILES)
                list(GET FLATBUFFERS_LIB_FILES 0 FIRST_FLATBUFFERS_LIB)
                get_filename_component(FIRST_FLATBUFFERS_LIB_NAME ${FIRST_FLATBUFFERS_LIB} NAME)
                message(STATUS "Creating symlink from ${FIRST_FLATBUFFERS_LIB_NAME} to expected library name")
                
                if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
                    execute_process(
                        COMMAND ln -sf ${FIRST_FLATBUFFERS_LIB_NAME} libflatbuffers.dylib
                        WORKING_DIRECTORY ${FLATBUFFERS_INSTALL_DIR}/lib
                    )
                else()
                    execute_process(
                        COMMAND ln -sf ${FIRST_FLATBUFFERS_LIB_NAME} libflatbuffers.so
                        WORKING_DIRECTORY ${FLATBUFFERS_INSTALL_DIR}/lib
                    )
                endif()
            else()
                # If no library files are found, try to build a static library and create a shared library
                message(STATUS "FlatBuffers shared library not found. Trying to build static library and create shared library...")
                
                # Reconfigure for static library
                execute_process(
                    COMMAND ${CMAKE_COMMAND} 
                        -G "${CMAKE_GENERATOR}"
                        -DCMAKE_INSTALL_PREFIX=${FLATBUFFERS_INSTALL_DIR}
                        -DCMAKE_BUILD_TYPE=Release
                        -DCMAKE_CXX_STANDARD=17
                        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                        -DFLATBUFFERS_BUILD_TESTS=OFF
                        -DFLATBUFFERS_BUILD_FLATLIB=ON
                        -DFLATBUFFERS_BUILD_FLATC=OFF
                        -DFLATBUFFERS_BUILD_FLATHASH=OFF
                        -DFLATBUFFERS_INSTALL=ON
                        -DBUILD_SHARED_LIBS=ON
                        ${FLATBUFFERS_SOURCE_DIR}
                    WORKING_DIRECTORY ${FLATBUFFERS_BUILD_DIR}
                )
                
                # Build static library
                execute_process(
                    COMMAND ${CMAKE_COMMAND} --build . --config Release
                    WORKING_DIRECTORY ${FLATBUFFERS_BUILD_DIR}
                )
                
                # Install static library
                execute_process(
                    COMMAND ${CMAKE_COMMAND} --install . --config Release
                    WORKING_DIRECTORY ${FLATBUFFERS_BUILD_DIR}
                )
                
                # Create shared library from static library
                if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
                    execute_process(
                        COMMAND ${CMAKE_CXX_COMPILER} -shared -o libflatbuffers.dylib -Wl,-all_load libflatbuffers.a -Wl,-noall_load
                        WORKING_DIRECTORY ${FLATBUFFERS_INSTALL_DIR}/lib
                    )
                else()
                    execute_process(
                        COMMAND ${CMAKE_CXX_COMPILER} -shared -o libflatbuffers.so -Wl,--whole-archive libflatbuffers.a -Wl,--no-whole-archive
                        WORKING_DIRECTORY ${FLATBUFFERS_INSTALL_DIR}/lib
                    )
                endif()
            endif()
        endif()
        
        message(STATUS "FlatBuffers successfully built and installed to ${FLATBUFFERS_INSTALL_DIR}")
    else()
        message(STATUS "FlatBuffers is already installed in ${FLATBUFFERS_INSTALL_DIR}")
    endif()
    
    # Export installation path as cache variables for use elsewhere
    set(FLATBUFFERS_INCLUDE_DIR ${FLATBUFFERS_INSTALL_DIR}/include CACHE PATH "FlatBuffers include directory")
    set(FLATBUFFERS_LIBRARY_DIR ${FLATBUFFERS_INSTALL_DIR}/lib CACHE PATH "FlatBuffers library directory")
    
    # Set library file path (based on operating system)
    if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(FLATBUFFERS_LIBRARY ${FLATBUFFERS_INSTALL_DIR}/lib/libflatbuffers.dylib CACHE FILEPATH "FlatBuffers library")
    else()
        set(FLATBUFFERS_LIBRARY ${FLATBUFFERS_INSTALL_DIR}/lib/libflatbuffers.so CACHE FILEPATH "FlatBuffers library")
    endif()
    
    # Print configured installation directory
    message(STATUS "Configured FlatBuffers installation directory: ${FLATBUFFERS_INSTALL_DIR}")
    message(STATUS "FlatBuffers include directory: ${FLATBUFFERS_INCLUDE_DIR}")
    message(STATUS "FlatBuffers library: ${FLATBUFFERS_LIBRARY}")
endfunction()
