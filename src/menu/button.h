#pragma once

#include "../rendering/mesh.h"

class Button {
    private:
        float x;
        float y;
        float width;
        float height;
        bool visible;
        bool pressed;
        rendering::mesh shape;

        std::vector<float> get_vertices();
    public:
        Button();
        Button(float x, float y, float width, float height);
        void render();
        bool is_visible();
        void set_visible(bool state);
        bool is_pressed();
        void set_pressed(bool state);
        //detect if button was clicked with mouse click
        bool collision(const double& mouse_x, const double& mouse_y);
        void on_mouse_release();
};