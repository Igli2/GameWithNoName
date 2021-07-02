#include "game_window.h"

game_window::game_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler)
    : render_window{title, width, height, resizable, ev_handler}, off_x{0} {
    // button test
    Button button{10.0f, 10.0f, 100.0f, 80.0f};
    this->add_widget(std::move(button));

    // set initial resource menu size
    int w, h;
    this->get_window_size(&w, &h);
    this->resource_menu.updateWindowSize(w, h);
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

game_window::~game_window() {

}