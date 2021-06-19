#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace rendering {
    class render_window;
}

namespace event {
    typedef void(*key_event)(rendering::render_window* window, int key, int scancode, int action, int mods);
    typedef void(*mouse_event)(rendering::render_window* window, double xpos, double ypos);
}