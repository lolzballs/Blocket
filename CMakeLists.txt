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

add_executable(Blocket ${HDRS} ${SRCS})

# OpenGL
find_package(OpenGL REQUIRED)
