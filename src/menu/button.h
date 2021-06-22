#pragma once

#include "../rendering/mesh.h"

class Button {
    private:
        float x;
        float y;
        float width;
        float height;
        bool visible;
        rendering::mesh shape;

        std::vector<float> get_vertices();
    public:
        Button();
        Button(float x, float y, float width, float height);
        void render();
        bool is_visible();
        void set_visible(bool state);
};