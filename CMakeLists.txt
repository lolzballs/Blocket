project(Blocket)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Blocket_SOURCE_DIR}/cmake")

add_definitions(-DGLM_FORCE_RADIANS -DGLM_FORCE_PURE)

# Lets LOAD app our headers!
file(GLOB_RECURSE HDRS ${Blocket_SOURCE_DIR}/src/*.h)

# Lets LOAD app our sources!
file(GLOB_RECURSE SRCS
        ${Blocket_SOURCE_DIR}/src/*.cpp
        ${Blocket_SOURCE_DIR}/src/*.c
)

# C++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Blocket ${HDRS} ${SRCS})

if (NOT DEFINED EMSCRIPTEN)
    # OpenGL
    find_package(OpenGL REQUIRED)

    # GLEW
    find_package(GLEW REQUIRED)

    # SDL2
    find_package(SDL2 REQUIRED)
	
	# GLM
	find_package(GLM REQUIRED)

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
endif(NOT DEFINED EMSCRIPTEN)
