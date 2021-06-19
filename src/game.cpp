#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "rendering/render_window.h"
#include "events/event_handler.h"
#include "rendering/shader.h"

void on_esc_press(rendering::render_window* window, int key, int scancode, int action, int mods);

int main() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};

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


	uint vao;
	uint vbo;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(vao);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	test_shader.use();
	while(window.is_open()) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);

    	window.update();
	}

	glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

	glfwTerminate();

	return 0;
}

void on_esc_press(rendering::render_window* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		window->close();
	}
}