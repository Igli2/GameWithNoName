#pragma once

#include "../rendering/mesh.h"
#include "../utils/registry.h"
#include "../rendering/shader.h"
#include "../rendering/font.h"

#include "button.h"

class SettingScrollSpeedButton : public Button {
    public:
        SettingScrollSpeedButton();
        SettingScrollSpeedButton(float x, float y, float width, float height);
        void callback();
};

class SettingsMenu {
    private:
        const float MARGIN_LEFT_RIGHT = 100;

        bool visible;
        rendering::mesh background;
		utils::registry<rendering::shader_program>* shader_registry;
		utils::registry<rendering::font>* font_registry;
        SettingScrollSpeedButton setting_scroll_speed_button;

    public:
        SettingsMenu(const int width, const int height);
        void setVisible(bool state);
        bool isVisible();
		void set_shader_registry(utils::registry<rendering::shader_program>* shader_registry);
		void set_font_registry(utils::registry<rendering::font>* font_registry);
        void render();
        void on_mouse_press(const double& x, const double& y);
        void on_mouse_release(const double& x, const double& y);
};