#pragma once

#include <vector>

#include "events.h"

namespace rendering {
    class render_window;
}

namespace event {
    class event_handler {
        private:
            std::vector<key_event> key_events;
        public:
            event_handler();
            void add_key_event(const key_event event);
            bool remove_key_event(const key_event event);
            void key_press_callback(rendering::render_window* window, int key, int scancode, int action, int mods);
            ~event_handler();
    };    
}