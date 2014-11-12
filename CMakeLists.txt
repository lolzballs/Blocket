project(Blocket)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

# Lets LOAD app our headers!
file(GLOB_RECURSE HDRS ${Blocket_SOURCE_DIR}/src/*.h)

# Lets LOAD app our sources!
file(GLOB_RECURSE SRCS
        ${Blocket_SOURCE_DIR}/src/*.cpp
        ${Blocket_SOURCE_DIR}/src/*.c
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(Blocket ${HDRS} ${SRCS})

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

# SDL2
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(GLFW3 REQUIRED glfw3)

# Define the include DIRs
include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries(Blocket
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${GLFW3_LIBRARIES}
)
