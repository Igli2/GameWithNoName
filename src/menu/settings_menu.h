#pragma once

#include <vector>
#include <map>

#include "../rendering/mesh.h"
#include "../utils/registry.h"
#include "../rendering/shader.h"
#include "../rendering/font.h"

#include "empty_menu.h"
#include "button.h"

class SettingButton : public Button {
    private:
        std::string key;
        std::vector<int> values;
        int current;
        std::map<std::string, int>* settings;

    public:
        SettingButton(float x, float y, float width, float height, std::string key, std::vector<int> values, std::map<std::string, int>* settings);
        void callback();
};

class SettingsMenu : public EmptyMenu {
    private:
        rendering::mesh background;
		utils::registry<rendering::shader_program>* shader_registry;
		utils::registry<rendering::font>* font_registry;
        std::vector<SettingButton> setting_buttons;
        std::map<std::string, int> settings;

    public:
        SettingsMenu(const int width, const int height);
        void render() override;
        void on_mouse_press(const double& x, const double& y);
        void on_mouse_release(const double& x, const double& y);
        std::map<std::string, int>* get_settings();
};