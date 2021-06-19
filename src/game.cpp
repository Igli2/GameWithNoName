#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "rendering/render_window.h"
#include "events/event_handler.h"

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

	// create a vertex shader
	const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// shader errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if(!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "**VERTEX SHADER ERROR**\n" << infoLog << std::endl;
	}

	// create fragment shader
	const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main() {\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// shader errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if(!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "**FRAGMENT SHADER ERROR**\n" << infoLog << std::endl;
	}

	// shader program
	uint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// program link errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "**SHADER PROGRAM LINK ERROR**\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	while(window.is_open()) {
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);

    	window.update();
	}

	glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);

	glfwTerminate();

	return 0;
}

void on_esc_press(rendering::render_window* window, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		window->close();
	}
}