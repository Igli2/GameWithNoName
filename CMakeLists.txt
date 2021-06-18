cmake_minimum_required(VERSION 3.20.3)
set (CMAKE_CXX_STANDARD 20)

project(GameWithNoName)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glad)
add_subdirectory(glfw)

add_executable(main src/main.cpp)

target_link_libraries(main glad ${OPENGL_LIBRARIES} glfw)