#pragma once

#include <string>

#include "events/event_handler.h"
#include "rendering/render_window.h"

// The custom class inherits from render_window
class custom_window : public rendering::render_window {
    private:
		int custom_attribute;

		void custom_method();

    public:
		custom_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler);
		~custom_window();
};