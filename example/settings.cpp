#include <iostream>

#include "menu/settings_menu.h"

class CustomClass {
    private:
        std::map<std::string, int>* settings;

    public:
        // pass the settings map pointer to custom class to use
        CustomClass(std::map<std::string, int>* settings): settings{settings} {}

        void test_method() {
            // access a specific setting value
            std::cout << this->settings->at("setting_name") << std::endl;
        }
};

int main() {
    // instance of settings menu (game_window.h / game_window.cpp)
    SettingsMenu menu{600, 800};

    // get the settings map
    std::map<std::string, int>* settings = menu.get_settings();

    // custom class instance
    CustomClass cc{settings};
    cc.test_method();
}