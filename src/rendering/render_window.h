#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <cstddef>

#include "../events/event_handler.h"

namespace rendering {
    class render_window {
        private:
            GLFWwindow* window;

        protected:
            event::event_handler& ev_handler;

        public:
            render_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler);
            bool is_open();
            void update();
            void key_press_event(int key, int scancode, int action, int mods);
            void mouse_move_event(double xpos, double ypos);
            void mouse_button_event(int button, int action, int mods);
            void scroll_event(double xoffset, double yoffset);
            void close();
            virtual ~render_window();
    };    
}
