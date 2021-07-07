#include <iostream>

#include "game_window.h"

game_window::game_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler)
    : render_window{title, width, height, resizable, ev_handler}, off_x{0}, resource_menu{(int)width, (int)height} {
    // button test
    Button button{10.0f, 10.0f, 100.0f, 80.0f};
    this->add_widget(std::move(button));

    // set initial resource menu size
    this->resource_menu.addResources(Resource::BEECH_LOG, 10);
    this->resource_menu.removeResources(Resource::BEECH_LOG, 2);
}

void game_window::add_widget(Button button) {
    this->widgets.push_back(std::move(button));
}

void game_window::render_widgets() {
    for (Button& button : this->widgets) {
        // button.render();
    }
    this->resource_menu.render();
}

void game_window::on_mouse_button_press(rendering::render_window* window, int button, int action, int mods) {
    double x, y;
    window->get_mouse_position(&x, &y);

    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            for (Button& b : this->widgets) {
                if (b.collision(x, y)) {
                    b.set_pressed(true);
                    break;
                }
            }
        }
    } else {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            for (Button& b : this->widgets) {
                b.on_mouse_release();
            }
        }
    }
}

void game_window::on_key_press(rendering::render_window* window, int key, int scancode, int action, int mods) {
    // std::cout << "REEEE" << std::endl;
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_R) {
            this->resource_menu.setVisible(!this->resource_menu.isVisible());
        }
    }
}

void game_window::set_shader_registry(utils::registry<rendering::shader_program>* shader_registry) {
    this->shader_registry = shader_registry;
    this->resource_menu.set_shader_registry(shader_registry);
}

void game_window::set_font_registry(utils::registry<rendering::font>* font_registry) {
    this->font_registry = font_registry;
    this->resource_menu.set_font_registry(font_registry);
}

game_window::~game_window() {

}