#include "button.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Button::Button(): Button{0, 0, 0, 0} {}

Button::Button(float x, float y, float width, float height): x{x}, y{y}, width{width}, height{height}, visible{true}, pressed{false}, text{} {
    std::vector<float> vertices = this->get_vertices();

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

    this->shape = std::move(rendering::mesh::create_with_color(GL_STATIC_DRAW, 2, vertices, indices, color));
}

void Button::render(utils::registry<rendering::shader_program>* shader_registry, utils::registry<rendering::font>* font_registry) {
    if (this->visible) {
        this->shape.draw();

        shader_registry->get("font_shader").use();

        // fit text size to button size
        float text_size = 1.0f;
        vec2<float> text_dimensions = font_registry->get("example_font").get_string_render_bounds(this->text, 1.0f);
        text_size = std::min((this->width - 10) / text_dimensions.x, (this->height - 10) / text_dimensions.y);

        text_dimensions = font_registry->get("example_font").get_string_render_bounds(this->text, text_size);
        glm::mat4 text_pos{1.0f};
        text_pos = glm::translate(text_pos, glm::vec3{this->x + (this->width - text_dimensions.x) / 2, this->y + (this->height - text_dimensions.y) / 2, 0.0f});
        font_registry->get("example_font").draw_string(this->text, text_size, vec4<float>{0.78f, 0.29f, 0.44f, 1.0f}, text_pos);
    }
}

std::vector<float> Button::get_vertices() {
    std::vector<float> vertices{{
        this->x, this->y,
        this->x + this->width, this->y,
        this->x, this->y + this->height,
        this->x + this->width, this->y + this->height
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

void Button::on_mouse_press(const double& mouse_x, const double& mouse_y) {
    if (this->visible) {
        if (mouse_x >= this->x && mouse_x <= this->x + this->width) {
            if (mouse_y >= this->y && mouse_y <= this->y + this->height) {
                this->pressed = true;
            }
        }
    }
}

void Button::on_mouse_release(const double& mouse_x, const double& mouse_y) {
    if (this->visible && this->pressed) {
        if (mouse_x >= this->x && mouse_x <= this->x + this->width) {
            if (mouse_y >= this->y && mouse_y <= this->y + this->height) {
                this->callback();
            }
        }
    }

    this->pressed = false;
}

void Button::callback() {}