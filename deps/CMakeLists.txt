CMAKE_MINIMUM_REQUIRED (VERSION 3.4)

PROJECT (deps)

SET(BUILD_TESTING flase)

#指定头文件路径
include_directories(${PROJECT_SOURCE_DIR})

#编译文件
ADD_LIBRARY(glad glad/glad.h glad.c)

#输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_ROOT_DIR}/build/bin)

#设置编译选项
if(WIN32)
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11")
elseif(UNIX)
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -g")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -O3")
endif()