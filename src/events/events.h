#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace event {
    typedef void(*key_event)(GLFWwindow* window, int key, int scancode, int action, int mods);
}