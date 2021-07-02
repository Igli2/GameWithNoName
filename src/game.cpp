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

#include "utils/registry.h"

#include "game_window.h"

void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods);
void register_shaders(utils::registry<rendering::shader_program>& shader_registry);
void register_textures(utils::registry<rendering::texture>& texture_registry);
rendering::shader_program load_shader(const std::string& vert_path, const std::string& frag_path);

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

	game_window window{"Game", WINDOW_WIDTH, WINDOW_HEIGHT, false, ev_handler};

	utils::registry<rendering::shader_program> shader_registry;
	register_shaders(shader_registry);

	utils::registry<rendering::texture> texture_registry;
	register_textures(texture_registry);

	ev_handler.add_mouse_button_event(on_mouse_button_press);

	rendering::shader_program& overlay_shader = shader_registry.get("overlay_shader");

	const int window_bounds_location = overlay_shader.get_uniform_location("window_bounds");
	const int offset_location = overlay_shader.get_uniform_location("offset");
	const int has_texture_location = overlay_shader.get_uniform_location("has_texture");
	const int use_color_location = overlay_shader.get_uniform_location("use_color");

	rendering::mesh rect = rendering::mesh::create(GL_STATIC_DRAW, 2, vertices, indices);

	rendering::buffer tex_buf = rendering::buffer::create(tex_coords.size() * sizeof(float), &tex_coords[0], GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	rect.set_data(1, tex_buf, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	rendering::buffer col_buf = rendering::buffer::create(vertices_color.size() * sizeof(float), &vertices_color[0], GL_ARRAY_BUFFER, GL_STATIC_DRAW);
	rect.set_data(2, col_buf, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	overlay_shader.use();
	glUniform2f(window_bounds_location, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	glUniform2f(offset_location, 600.0f, 299.0f);
	glUniform1i(has_texture_location, 1);
	glUniform1i(use_color_location, 1);

	texture_registry.get("example_texture").use();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	while(window.is_open()) {
		glClear(GL_COLOR_BUFFER_BIT);

		rect.draw();
		window.render_widgets();

    	window.update();
	}

	glfwTerminate();

	return 0;
}

void on_mouse_button_press(rendering::render_window* window, int button, int action, int mods) {
	game_window* w = (game_window*) window;
	w->on_mouse_button_press(w, button, action, mods);
}

void register_shaders(utils::registry<rendering::shader_program>& shader_registry) {
	shader_registry.insert("overlay_shader", std::move(load_shader("../res/shaders/vertex_shaders/overlay_texture_shader.vs",
																   "../res/shaders/fragment_shaders/overlay_texture_shader.fs")));
}

void register_textures(utils::registry<rendering::texture>& texture_registry) {
	texture_registry.insert("example_texture", std::move(rendering::texture::load_from_file("../res/textures/test.png",
														 GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT, GL_RGB)));
}

rendering::shader_program load_shader(const std::string& vert_path, const std::string& frag_path) {
	std::ifstream frag_shader{frag_path};
	std::ifstream vert_shader{vert_path};

	if(!frag_shader.is_open() || !vert_shader.is_open()) throw std::runtime_error("Unable to open one of the shader files!");

	std::vector<rendering::shader> shaders;
	shaders.push_back(std::move(rendering::shader::from_stream(frag_shader, GL_FRAGMENT_SHADER)));
	shaders.push_back(std::move(rendering::shader::from_stream(vert_shader, GL_VERTEX_SHADER)));

	frag_shader.close();
	vert_shader.close();

	return std::move(rendering::shader_program{shaders});
}