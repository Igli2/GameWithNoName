cmake_minimum_required(VERSION 3.18.4)
set (CMAKE_CXX_STANDARD 14)

project(GameWithNoName)

find_package(Freetype REQUIRED)
find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL "GLFW lib only")

add_subdirectory(glad)
add_subdirectory(glfw)
add_subdirectory(json_library)
add_subdirectory(assimp)

set(SOURCE_FILES
    src/game_window.cpp
    src/rendering/render_window.cpp
    src/rendering/buffer.cpp
    src/rendering/vao.cpp
    src/rendering/shader.cpp
    src/rendering/mesh.cpp
    src/rendering/texture.cpp
    src/rendering/font.cpp
    src/rendering/camera.cpp
    src/rendering/model_loader.cpp
    src/rendering/model.cpp
    src/events/event_handler.cpp
    src/menu/resource_menu.cpp
    src/menu/settings_menu.cpp
    src/menu/button.cpp
    src/menu/empty_menu.cpp

    src/game_window.h
    src/rendering/render_window.h
    src/rendering/buffer.h
    src/rendering/vao.h
    src/rendering/shader.h
    src/rendering/mesh.h
    src/rendering/texture.h
    src/rendering/shader_constants.h
    src/rendering/vec.h
    src/rendering/font.h
    src/rendering/camera.h
    src/rendering/model_loader.h
    src/rendering/model.h
    src/events/event_handler.h
    src/events/events.h
    src/menu/resource_menu.h
    src/menu/settings_menu.h
    src/menu/resource.h
    src/menu/button.h
    src/menu/empty_menu.h
    src/utils/registry.h

    src/utils/registry.ipp

    ${JSON_LIBRARY_FILES}
)

include_directories(${FREETYPE_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} includes/ json_library/src/lib/ glm/ assimp/include/ build/assimp/include/)

add_executable(game src/game.cpp ${SOURCE_FILES})

target_link_libraries(game glad ${OPENGL_LIBRARIES} glfw json_lib ${FREETYPE_LIBRARIES} assimp)