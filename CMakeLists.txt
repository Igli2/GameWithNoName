cmake_minimum_required(VERSION 3.20.3)
set (CMAKE_CXX_STANDARD 11)

project(GameWithNoName)

find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} )

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glad)
add_subdirectory(glfw)

set(SOURCE_FILES
    src/rendering/render_window.cpp
    src/rendering/shader.cpp
    src/rendering/mesh.cpp
    src/events/event_handler.cpp
    src/menu/resource_menu.cpp
    src/menu/button.cpp

    src/rendering/render_window.h
    src/rendering/shader.h
    src/rendering/mesh.h
    src/events/event_handler.h
    src/events/events.h
    src/menu/resource_menu.h
    src/menu/button.h
)

add_executable(game src/game.cpp ${SOURCE_FILES})

target_link_libraries(game glad ${OPENGL_LIBRARIES} glfw)