#include <fstream>
#include <stdexcept>
#include <vector>
#include <cstddef>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#undef STB_IMAGE_IMPLEMENTATION

#include "rendering/render_window.h"
#include "rendering/shader.h"
#include "rendering/texture.h"
#include "rendering/shader_constants.h"
#include "rendering/font.h"

#include "utils/registry.h"

#include "game_window.h"

void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods);
void on_key_press(rendering::render_window* window, int key, int scancode, int action, int mods);
void register_shaders(utils::registry<rendering::shader_program>& shader_registry);
void register_textures(utils::registry<rendering::texture>& texture_registry);
void register_fonts(utils::registry<rendering::font>& font_registry);
rendering::shader load_shader(const std::string& path, GLenum type);
rendering::shader_program load_shader_program(const std::string& vert_path, const std::string& frag_path);

const size_t WINDOW_WIDTH = 800;
const size_t WINDOW_HEIGHT = 600;

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

	utils::registry<rendering::shader_program> shader_registry;
	register_shaders(shader_registry);

	utils::registry<rendering::texture> texture_registry;
	register_textures(texture_registry);

	utils::registry<rendering::font> font_registry;
	register_fonts(font_registry);

	ev_handler.add_mouse_button_event(on_mouse_button_press);
	ev_handler.add_key_event(on_key_press);
	
	rendering::mesh rect = rendering::mesh::create_with_texture_and_color(GL_STATIC_DRAW, 2, vertices, indices, tex_coords, vertices_color);
	rect.set_texture_usage(false);

	shader_registry.get("overlay_shader").use();
	glUniform2f(shader_const::WINDOW_BOUNDS_LOCATION, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

	shader_registry.get("font_shader").use();
	glUniform2f(shader_const::WINDOW_BOUNDS_LOCATION, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	while(window.is_open()) {
		glClear(GL_COLOR_BUFFER_BIT);

		shader_registry.get("overlay_shader").use();

		texture_registry.get("example_texture").use();
		rect.draw(vec3<float>{100.0f, 200.0f, 0.0f});

		window.render_widgets();

		shader_registry.get("font_shader").use();

		font_registry.get("example_font").draw_string("Hello World!", 0.75f, vec4<float>{0.78f, 0.59f, 0.24f, 1.0f}, vec3<float>{0.0f, 50.0f, 0.0f});

    	window.update();
	}

	glfwTerminate();

	return 0;
}

void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods) {
	game_window* w = (game_window*) window;
	w->on_mouse_button_press(w, button, action, mods);
}

void on_key_press(rendering::render_window* window, int key, int scancode, int action, int mods) {
	game_window* w = (game_window*) window;
	w->on_key_press(w, key, scancode, action, mods);
}

void register_shaders(utils::registry<rendering::shader_program>& shader_registry) {
	shader_registry.insert("overlay_shader", std::move(load_shader_program("../res/shaders/vertex_shaders/overlay_texture_shader.vs",
																   "../res/shaders/fragment_shaders/overlay_texture_shader.fs")));
	shader_registry.insert("font_shader", std::move(load_shader_program("../res/shaders/vertex_shaders/font_shader.vs",
																   "../res/shaders/fragment_shaders/font_shader.fs")));
}

void register_textures(utils::registry<rendering::texture>& texture_registry) {
	texture_registry.insert("example_texture", std::move(rendering::texture::load_from_file("../res/textures/test.png",
														 GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, GL_RGB)));
}

void register_fonts(utils::registry<rendering::font>& font_registry) {
	font_registry.insert("example_font", std::move(rendering::font::load_from_file("../res/fonts/tourney_black.ttf", 64)));
}

rendering::shader load_shader(const std::string& path, GLenum type) {
	std::ifstream shader_src{path};

	if(!shader_src.is_open()) throw std::runtime_error("Unable to open file '" + path + "'!");

	rendering::shader s = rendering::shader::from_stream(shader_src, type);

	shader_src.close();

	return s;
}

rendering::shader_program load_shader_program(const std::string& vert_path, const std::string& frag_path) {
	std::vector<rendering::shader> shaders;

	shaders.push_back(load_shader(vert_path, GL_VERTEX_SHADER));
	shaders.push_back(load_shader(frag_path, GL_FRAGMENT_SHADER));

	return rendering::shader_program{shaders};
}