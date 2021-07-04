#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include "rendering/render_window.h"
#include "rendering/shader.h"
#include "rendering/mesh.h"
#include "rendering/texture.h"
#include "rendering/buffer.h"
#include "rendering/vao.h"
#include "events/event_handler.h"
#include "menu/resource_menu.h"
#include "menu/button.h"

class game_window;
void on_key_press(rendering::render_window* window, int key, int scancode, int action, int mods);
void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods);

class game_window : public rendering::render_window {
	private:
		float off_x;
		std::vector<Button> widgets;
		ResourceMenu resource_menu;

	public:
		game_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler)
		 : render_window{title, width, height, resizable, ev_handler}, off_x{0}, resource_menu{(int)width, (int)height} {
			// button test
			Button button{10.0f, 10.0f, 100.0f, 80.0f};
			this->add_widget(std::move(button));

			// resource menu test
			this->resource_menu.addResources(Resource::BEECH_LOG, 10);
			this->resource_menu.removeResources(Resource::BEECH_LOG, 2);
		}

		float get_off_x() const {
			return this->off_x;
		}

		void set_off_x(const float value) {
			this->off_x = value;
		}

		void add_widget(Button button) {
			this->widgets.push_back(std::move(button));
		}

		void render_widgets() {
			for (Button& button : this->widgets) {
				// button.render();
			}
			this->resource_menu.render();
		}

		// checks all button widgets if they were pressed / released
		void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods) {
			double x, y;
			window->get_mouse_position(&x, &y);

			if (action == GLFW_PRESS) {
				if (button == GLFW_MOUSE_BUTTON_LEFT) {
					for (Button& b : this->widgets) {
						if (b.collision(x, y)) {
							b.set_pressed(true);
							break;
						}
					}
				}
			} else {
				if (button == GLFW_MOUSE_BUTTON_LEFT) {
					for (Button& b : this->widgets) {
						b.on_mouse_release();
					}
				}
			}
		}
};

constexpr size_t WINDOW_WIDTH = 800;
constexpr size_t WINDOW_HEIGHT = 600;

int main() {
	std::vector<float> vertices{{
		0.0f, 0.0f,
		200.0f, 0.0f,
		200.0f, 300.0f,
		0.0f, 300.0f
	}};

	std::vector<float> tex_coords{{
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	}};

	std::vector<float> vertices_color{{
		1.0f, 0.7f, 0.2f, 1.0f,
		0.0f, 0.37f, 0.7f, 1.0f,
		0.3f, 0.23f, 0.2f, 1.0f,
		0.64f, 1.0f, 0.6f, 1.0f
	}};

	std::vector<unsigned int> indices{{
		0, 1, 3,
		1, 2, 3
	}};

	// init window & attributes
	event::event_handler ev_handler{};
	game_window window{"Game", WINDOW_WIDTH, WINDOW_HEIGHT, true, ev_handler};

	ev_handler.add_key_event(on_key_press);
	ev_handler.add_mouse_button_event(on_mouse_button_press);

	std::ifstream frag_shader{"../res/shaders/fragment_shaders/overlay_texture_shader.fs"};
	std::ifstream vert_shader{"../res/shaders/vertex_shaders/overlay_texture_shader.vs"};

	if(!frag_shader.is_open() || !vert_shader.is_open()) {
		std::cerr << "Unable to open shader files!" << std::endl;
		return -1;
	}

	std::vector<rendering::shader> shaders;
	shaders.push_back(std::move(rendering::shader::from_stream(frag_shader, GL_FRAGMENT_SHADER)));
	shaders.push_back(std::move(rendering::shader::from_stream(vert_shader, GL_VERTEX_SHADER)));

	frag_shader.close();
	vert_shader.close();

	rendering::shader_program texture_shader{shaders};
	const int window_bounds_location = texture_shader.get_uniform_location("window_bounds");
	const int offset_location = texture_shader.get_uniform_location("offset");
	const int has_texture_location = texture_shader.get_uniform_location("has_texture");
	const int use_color_location = texture_shader.get_uniform_location("use_color");

	rendering::mesh rect = rendering::mesh::create(GL_STATIC_DRAW, 2, vertices, indices);

	rendering::buffer tex_buf = rendering::buffer::create(tex_coords.size() * sizeof(float), &tex_coords[0], GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	rect.set_data(1, tex_buf, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	rendering::buffer col_buf = rendering::buffer::create(vertices_color.size() * sizeof(float), &vertices_color[0], GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	rect.set_data(2, col_buf, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	rendering::texture tex = rendering::texture::load_from_file("../res/textures/test.png", GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, GL_RGB);
	
	texture_shader.use();
	glUniform2f(window_bounds_location, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	// glUniform2f(offset_location, 600.0f, 299.0f);
	glUniform1i(has_texture_location, 1);
	glUniform1i(use_color_location, 1);

	tex.use();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	while(window.is_open()) {
		glClear(GL_COLOR_BUFFER_BIT);

		// rect.draw();
		window.render_widgets();

    	window.update();
	}

	glfwTerminate();

	return 0;
}

void on_key_press(rendering::render_window* window, int key, int scancode, int action, int mods) {
	game_window* w = (game_window*) window;
	if(action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_ESCAPE:
				window->close();
				break;
			case GLFW_KEY_A:
				w->set_off_x(w->get_off_x() - 0.1f);
				break;
			case GLFW_KEY_D:
				w->set_off_x(w->get_off_x() + 0.1f);
				break;
		}
	}
}

void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods) {
	game_window* w = (game_window*) window;
	w->on_mouse_button_press(w, button, action, mods);
}