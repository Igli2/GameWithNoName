#include <iostream>

#include "game_window.h"

game_window::game_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler)
    : render_window{title, width, height, resizable, ev_handler}, resource_menu{(int)width, (int)height}, settings_menu{(int)width, (int)height} {
    // resource menu test
    this->resource_menu.addResources(Resource::BEECH_LOG, 10);
    this->resource_menu.removeResources(Resource::BEECH_LOG, 2);
}

void game_window::render_menus() {
    this->resource_menu.render();
    this->settings_menu.render();
}

void game_window::on_mouse_button_press(rendering::render_window* window, int button, int action, int mods) {
    double x, y;
    window->get_mouse_position(&x, &y);

    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            /*for (Button& b : this->widgets) {
                if (b.collision(x, y)) {
                    b.set_pressed(true);
                    break;
                }
            }*/
            this->settings_menu.on_mouse_press(x, y);
        }
    } else {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            /*for (Button& b : this->widgets) {
                b.on_mouse_release();
            }*/
            this->settings_menu.on_mouse_release(x, y);
        }
    }
}

void game_window::on_key_press(rendering::render_window* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_R) {
            // toggle resource menu visibility
            this->settings_menu.setVisible(false);
            this->resource_menu.setVisible(!this->resource_menu.isVisible());
        } else if (key == GLFW_KEY_O) {
            // toggle settings menu visibility
            this->resource_menu.setVisible(false);
            this->settings_menu.setVisible(!this->settings_menu.isVisible());
        }
    }
}

void game_window::on_scroll(rendering::render_window* window, double xoffset, double yoffset) {
    this->resource_menu.on_scroll(yoffset);
}

void game_window::set_shader_registry(utils::registry<rendering::shader_program>* shader_registry) {
    this->shader_registry = shader_registry;
    this->resource_menu.set_shader_registry(shader_registry);
    this->settings_menu.set_shader_registry(shader_registry);
}

void game_window::set_font_registry(utils::registry<rendering::font>* font_registry) {
    this->font_registry = font_registry;
    this->resource_menu.set_font_registry(font_registry);
    this->settings_menu.set_font_registry(font_registry);
}

game_window::~game_window() {

}