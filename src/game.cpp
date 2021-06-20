#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "rendering/render_window.h"
#include "events/event_handler.h"
#include "rendering/shader.h"
#include "rendering/mesh.h"
#include "menu/menu.h"

void on_esc_press(rendering::render_window* window, int key, int scancode, int action, int mods);

int main() {
	//menu test
	Menu menu;
	menu.addResources(Resource::BEECH_LOG, 10);
	menu.removeResources(Resource::BEECH_LOG, 8);
	menu.removeResources(Resource::BEECH_LOG, 8);
	
	std::vector<float> vertices{{
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	}};

	std::vector<unsigned int> indices{{
		0, 1, 3,
		1, 2, 3
	}};

	// init window & attributes
	event::event_handler ev_handler{};
	rendering::render_window window{"Game", 800, 600, false, ev_handler};

	ev_handler.add_key_event(on_esc_press);

	std::ifstream frag_shader{"../res/shaders/fragment_shaders/test_shader.fs"};
	std::ifstream vert_shader{"../res/shaders/vertex_shaders/test_shader.vs"};

	if(!frag_shader.is_open() || !vert_shader.is_open()) {
		std::cerr << "Unable to open shader files!" << std::endl;
		return -1;
	}

	std::vector<rendering::shader> shaders;
	shaders.push_back(std::move(rendering::shader::from_stream(frag_shader, GL_FRAGMENT_SHADER)));
	shaders.push_back(std::move(rendering::shader::from_stream(vert_shader, GL_VERTEX_SHADER)));

	frag_shader.close();
	vert_shader.close();

	rendering::shader_program test_shader{shaders};

	rendering::mesh rect = std::move(rendering::mesh::create(vertices, indices, GL_STATIC_DRAW));
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	test_shader.use();
	while(window.is_open()) {
		glClear(GL_COLOR_BUFFER_BIT);

		rect.draw();

    	window.update();
	}

	glfwTerminate();

	return 0;
}

void on_esc_press(rendering::render_window* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		window->close();
	}
}