cmake_minimum_required(VERSION 3.0)
project(Blocket)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(vendor/glfw)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	set(CMAKE_CXX_STANDARD 11)
	add_definitions(-DNOMINMAX)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(src
                    vendor/glad/include/
                    vendor/glfw/include/
                    vendor/glm/
                    vendor/stb/)

file(GLOB VENDORS_SOURCES vendor/glad/src/glad.c)
file(GLOB PROJECT_SOURCES src/*.cpp src/*.h)
file(GLOB PROJECT_BLOCK_SOURCES src/block/*.cpp src/block/*.h)
file(GLOB PROJECT_WORLD_SOURCES src/world/*.cpp src/world/*.h)
file(GLOB PROJECT_UTIL_SOURCES src/util/*.cpp src/util/*.h)
file(GLOB PROJECT_SHADERS res/shaders/*.*)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          README.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("src" FILES ${PROJECT_SOURCES})
source_group("src\\block" FILES ${PROJECT_BLOCK_SOURCES})
source_group("src\\world" FILES ${PROJECT_WORLD_SOURCES})
source_group("src\\util" FILES ${PROJECT_UTIL_SOURCES})
source_group("shaders" FILES ${PROJECT_SHADERS})
source_group("vendor" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_BLOCK_SOURCES} ${PROJECT_WORLD_SOURCES} ${PROJECT_UTIL_SOURCES}
			${PROJECT_SHADERS} ${PROJECT_CONFIGS} ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
