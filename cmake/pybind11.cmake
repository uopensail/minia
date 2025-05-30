function(configure_pybind11)
    # 查找Python
    find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
    
    # 下载并配置pybind11
    include(FetchContent)
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v2.11.1
        GIT_SHALLOW TRUE
    )
    
    FetchContent_MakeAvailable(pybind11)
    
    # 设置Python相关变量供父作用域使用
    set(PYTHON3_EXECUTABLE ${Python3_EXECUTABLE} PARENT_SCOPE)
    set(PYTHON3_VERSION ${Python3_VERSION} PARENT_SCOPE)
    
    message(STATUS "Python executable: ${Python3_EXECUTABLE}")
    message(STATUS "Python version: ${Python3_VERSION}")
endfunction()
