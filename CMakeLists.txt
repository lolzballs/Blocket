project(Blocket)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)

add_definitions(-DGLM_FORCE_RADIANS)

# Lets LOAD app our headers!
file(GLOB_RECURSE HDRS ${Blocket_SOURCE_DIR}/src/*.h)

# Lets LOAD app our sources!
file(GLOB_RECURSE SRCS
        ${Blocket_SOURCE_DIR}/src/*.cpp
        ${Blocket_SOURCE_DIR}/src/*.c
)

# C++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_executable(Blocket ${HDRS} ${SRCS})

# OpenGL
find_package(OpenGL REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

INCLUDE(FindPkgConfig)

# GLM

# default search dirs
SET(_glm_HEADER_SEARCH_DIRS
    "/usr/include"
    "/usr/local/include")

# check environment variable
SET(_glm_ENV_ROOT_DIR "$ENV{GLM_ROOT_DIR}")

IF(NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)
    SET(GLM_ROOT_DIR "${_glm_ENV_ROOT_DIR}")
ENDIF(NOT GLM_ROOT_DIR AND _glm_ENV_ROOT_DIR)

# put user specified location at beginning of search
IF(GLM_ROOT_DIR)
    SET(_glm_HEADER_SEARCH_DIRS "${GLM_ROOT_DIR}"
                                "${GLM_ROOT_DIR}/include"
                                 ${_glm_HEADER_SEARCH_DIRS})
ENDIF(GLM_ROOT_DIR)

# locate header
FIND_PATH(GLM_INCLUDE_DIR "glm/glm.hpp"
    PATHS ${_glm_HEADER_SEARCH_DIRS})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLM DEFAULT_MSG
    GLM_INCLUDE_DIR)

IF(GLM_FOUND)
    SET(GLM_INCLUDE_DIRS "${GLM_INCLUDE_DIR}")

    MESSAGE(STATUS "GLM_INCLUDE_DIR = ${GLM_INCLUDE_DIR}")
ENDIF(GLM_FOUND)

# SDL2
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

# Define the include DIRs
include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
)

# Define the link libraries
target_link_libraries(Blocket
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${SDL2_LIBRARIES}
)
