#pragma once

#include "../utils/registry.h"

#include "../rendering/shader.h"
#include "../rendering/font.h"

class EmptyMenu  {
    private:
        bool visible;

        utils::registry<rendering::shader_program>* shader_registry;
		utils::registry<rendering::font>* font_registry;

    protected:
        // move to settings
        const float MARGIN_LEFT_RIGHT = 100;
    
    public:
        EmptyMenu();

        bool isVisible();
        void setVisible(bool state);
        void set_shader_registry(utils::registry<rendering::shader_program>* shader_registry);
        utils::registry<rendering::shader_program>* get_shader_registry();
		void set_font_registry(utils::registry<rendering::font>* font_registry);
        utils::registry<rendering::font>* get_font_registry();

        virtual void render();
};