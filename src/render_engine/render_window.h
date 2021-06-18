#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cstddef>

namespace rendering {
    class render_window {
        private:
            GLFWwindow* window;
        public:
            render_window(const std::string& title, const size_t width, const size_t height, const bool resizable);
            bool is_open();
            void update();
            ~render_window();
    };    
}
