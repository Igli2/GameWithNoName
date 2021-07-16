#include "settings_menu.h"

void SettingScrollSpeedButton::callback() {
    this->set_text("callback called :<");
}

SettingScrollSpeedButton::SettingScrollSpeedButton(): Button{} {}

SettingScrollSpeedButton::SettingScrollSpeedButton(float x, float y, float width, float height): Button{x, y, width, height} {}



SettingsMenu::SettingsMenu(const int width, const int height): visible{false}, setting_scroll_speed_button{SettingsMenu::MARGIN_LEFT_RIGHT + 20, (float)height - 80, 120, 60} {
    this->setting_scroll_speed_button.set_text("Click me :>");

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

void SettingsMenu::setVisible(bool state) {
    this->visible = state;
}

bool SettingsMenu::isVisible() {
    return this->visible;
}

void SettingsMenu::set_shader_registry(utils::registry<rendering::shader_program>* shader_registry) {
    this->shader_registry = shader_registry;
}

void SettingsMenu::set_font_registry(utils::registry<rendering::font>* font_registry) {
    this->font_registry = font_registry;
}

void SettingsMenu::render() {
    if (this->visible) {
        this->background.draw();
        this->setting_scroll_speed_button.render(this->shader_registry, this->font_registry);
    }
}

void SettingsMenu::on_mouse_press(const double& x, const double& y) {
    this->setting_scroll_speed_button.on_mouse_press(x, y);
}

void SettingsMenu::on_mouse_release(const double& x, const double& y) {
    this->setting_scroll_speed_button.on_mouse_release(x, y);
}