#pragma once

#include <string>
#include <cstddef>

#include "utils/registry.h"

#include "events/event_handler.h"

#include "rendering/render_window.h"
#include "rendering/font.h"
#include "rendering/shader.h"

#include "menu/resource_menu.h"
#include "menu/button.h"

class game_window : public rendering::render_window {
	private:
		float off_x;
		std::vector<Button> widgets;
		ResourceMenu resource_menu;
		utils::registry<rendering::shader_program>* shader_registry;
		utils::registry<rendering::font>* font_registry;

	public:
		game_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler);
		void add_widget(Button button);
		void render_widgets();
		// checks all button widgets if they were pressed / released
		void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods);
		void on_key_press(rendering::render_window* window, int key, int scancode, int action, int mods);
		void on_scroll(rendering::render_window* window, double xoffset, double yoffset);
		void set_shader_registry(utils::registry<rendering::shader_program>* shader_registry);
		void set_font_registry(utils::registry<rendering::font>* font_registry);
        ~game_window();
};