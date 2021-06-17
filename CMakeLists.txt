cmake_minimum_required(VERSION 3.20.3)
set (CMAKE_CXX_STANDARD 20)

project(GameWithNoName)

add_executable(main src/main.cpp)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(main glfw3)