#include <iostream>

#include "settings_menu.h"

void SettingButton::callback() {
    this->current += 1;
    if (this->current > this->values.size() - 1) {this->current = 0;}

    int new_value =this->values[this->current];
    this->set_text(this->key + ": " + std::to_string(new_value));
    this->settings->at(this->key) = new_value;
}

SettingButton::SettingButton(float x, float y, float width, float height, std::string key, std::vector<int> values, std::map<std::string, int>* settings): 
    Button{x, y, width, height}, key{key}, values{values}, settings{settings}, current{0} {
        this->set_text(this->key + ": " + std::to_string(this->settings->at(this->key)));
}



SettingsMenu::SettingsMenu(const int width, const int height): EmptyMenu{} {
        this->settings = {{"scroll_speed", 5}};

        SettingButton test_button{SettingsMenu::MARGIN_LEFT_RIGHT + 20, (float)height - 80, 160, 60, "scroll_speed", {5, 10, 15, 20}, &this->settings};
        this->setting_buttons.push_back(std::move(test_button));

        // create background
        float w = static_cast<float>(width);
        float h = static_cast<float>(height);

        std::vector<float> vertices{{
            SettingsMenu::MARGIN_LEFT_RIGHT, 0,
            w - SettingsMenu::MARGIN_LEFT_RIGHT, 0,
            SettingsMenu::MARGIN_LEFT_RIGHT, h,
            w - SettingsMenu::MARGIN_LEFT_RIGHT, h
        }};

        std::vector<unsigned int> indices{{
            0, 1, 2,
            1, 2, 3
        }};

        std::vector<float> color{{
            0.85, 0.7, 0.7, 0.4,
            0.7, 0.85, 0.7, 0.4,
            0.7, 0.7, 0.85, 0.4,
            0.85, 0.85, 0.7, 0.4
        }};

        this->background = std::move(rendering::mesh::create_with_color(GL_STATIC_DRAW, 2, vertices, indices, color));
}

void SettingsMenu::render() {
    if (this->isVisible()) {
        this->background.draw();
        for (SettingButton& button : this->setting_buttons) {
            button.render(this->get_shader_registry(), this->get_font_registry());
        }
    }
}

void SettingsMenu::on_mouse_press(const double& x, const double& y) {
    for (SettingButton& button : this->setting_buttons) {
        button.on_mouse_press(x, y);
    }
}

void SettingsMenu::on_mouse_release(const double& x, const double& y) {
    for (SettingButton& button : this->setting_buttons) {
        button.on_mouse_release(x, y);
    }
}

std::map<std::string, int>* SettingsMenu::get_settings() {
    return &this->settings;
}