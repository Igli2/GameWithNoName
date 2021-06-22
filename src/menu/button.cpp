#include "button.h"

#include <iostream>

Button::Button(): Button{0, 0, 0, 0} {}

Button::Button(float x, float y, float width, float height): x{x}, y{y}, width{width}, height{height}, visible{true} {
    std::vector<float> vertices = this->get_vertices();

	std::vector<unsigned int> indices{{
		0, 1, 2,
		1, 2, 3
	}};

    this->shape = std::move(rendering::mesh::create(vertices, indices, GL_STATIC_DRAW));
}

void Button::render() {
    if (this->visible) {
        this->shape.draw();
    }
}

std::vector<float> Button::get_vertices() {
    std::vector<float> vertices{{
        this->x, this->y, 0.0f,
        this->x + this->width, this->y, 0.0f,
        this->x, this->y + this->height, 0.0f,
        this->x + this->width, this->y + this->height, 0.0f
    }};

    return std::move(vertices);
}

bool Button::is_visible() {
    return this->visible;
}

void Button::set_visible(bool state) {
    this->visible = state;
}