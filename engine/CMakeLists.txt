CMAKE_MINIMUM_REQUIRED (VERSION 3.4)

PROJECT (genesis VERSION 0.0.1)

ADD_SUBDIRECTORY(image)

SET(BUILD_TESTING flase)

#指定头文件路径-----------------------------------------
INCLUDE_DIRECTORIES(${PROJECT_ROOT_DIR}/deps)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/core/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/core/interface)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/tools/include)

#-modules
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/log/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/image/include)

#读取Src目录--------------------------------------------
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
AUX_SOURCE_DIRECTORY(core/src DIR_SRCS)
AUX_SOURCE_DIRECTORY(tools/src DIR_SRCS)

#-modules
AUX_SOURCE_DIRECTORY(log/src DIR_SRCS)

#编译文件-----------------------------------------------
ADD_LIBRARY(${PROJECT_NAME} ${DIR_SRCS})

#输出路径-----------------------------------------------
# SET(LIBRARY_OUTPUT_PATH ${PROJECT_ROOT_DIR}/build/bin)

#链接库-------------------------------------------------
IF(WIN32)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3 glad wsimg freetype)
ELSEIF(APPLE)
    FIND_LIBRARY(frameworkCocoa Cocoa)
    FIND_LIBRARY(frameworkIOKit IOKit)
    FIND_LIBRARY(frameworkCoreVideo CoreVideo)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} glfw3 glad wsimg freetype pthread ${frameworkCocoa} ${frameworkIOKit} ${frameworkCoreVideo})
ELSEIF(UNIX)
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} GL glfw3 glad wsimg freetype pthread dl X11 Xi Xrandr Xxf86vm Xcursor Xinerama)
ENDIF()

#拷贝资源-----------------------------------------------
IF(WIN32)
    FILE(COPY ${PROJECT_SOURCE_DIR}/shader DESTINATION ${PROJECT_ROOT_DIR}/build/bin/${CMAKE_BUILD_TYPE})
    FILE(COPY ${PROJECT_SOURCE_DIR}/source DESTINATION ${PROJECT_ROOT_DIR}/build/bin/${CMAKE_BUILD_TYPE})
ELSE()
    FILE(COPY ${PROJECT_SOURCE_DIR}/shader DESTINATION ${PROJECT_ROOT_DIR}/build/bin)
    FILE(COPY ${PROJECT_SOURCE_DIR}/source DESTINATION ${PROJECT_ROOT_DIR}/build/bin)
ENDIF()



#设置编译选项-------------------------------------------
IF(WIN32)
    # DEBUG RELEASE
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -Wall")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -Wall")

ELSEIF(APPLE)
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -m64 -std=c++11 -O0 -Wall -g")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -m64 -std=c++11 -O3 -Wall")

ELSEIF(UNIX)
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -m64 -std=c++11 -O0 -Wall -g")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -m64 -std=c++11 -O3 -Wall")
ENDIF()
