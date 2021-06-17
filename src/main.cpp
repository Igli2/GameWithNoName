#include <iostream>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>

void renderLoop() {
}

int main(int argc, char** argv) {
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "GameWithNoName", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window)) {
		//process key events

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

    	glfwSwapBuffers(window);
    	glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}