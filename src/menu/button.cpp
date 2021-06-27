#include "button.h"

#include <iostream>

Button::Button(): Button{0, 0, 0, 0} {}

Button::Button(float x, float y, float width, float height): x{x}, y{y}, width{width}, height{height}, visible{true}, pressed{false}, text{} {
    std::vector<float> vertices = this->get_vertices();

	std::vector<unsigned int> indices{{
		0, 1, 2,
		1, 2, 3
	}};

    this->shape = std::move(rendering::mesh::create(vertices, indices, GL_STATIC_DRAW));
}

void Button::render() {
    if (this->visible) {
        // TODO: draw text
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

bool Button::is_pressed() {
    return this->pressed;
}

void Button::set_pressed(bool state) {
    this->pressed = state;
}

const std::string Button::get_text() {
    return this->text;
}

void Button::set_text(std::string text) {
    this->text = text;
}

bool Button::collision(const double& mouse_x, const double& mouse_y) {
    if (this->visible) {
        if (mouse_x >= this->x && mouse_x <= this->x + this->width) {
            if (mouse_y >= this->y && mouse_y <= this->y + this->height) {
                return true;
            }
        }
    }

    return false;
}

void Button::on_mouse_release() {
    if (this->pressed) {
        //TODO: call callback
        std::cout << "callback" << std::endl;
    }
    this->pressed = false;
}