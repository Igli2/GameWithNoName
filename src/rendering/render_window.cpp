#include "render_window.h"

#include <stdexcept>

using namespace rendering;

//helper_functions
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    ((render_window*)glfwGetWindowUserPointer(window))->key_press_callback(key, scancode, action, mods);
}



render_window::render_window(const std::string& title, const size_t width, const size_t height, const bool resizable, event::event_handler& ev_handler)
 : ev_handler(ev_handler) {
    if(!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window!");
	}

    glfwMakeContextCurrent(this->window);

    if(!gladLoadGL()) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD!");
    }

    glViewport(0, 0, width, height);
    if(resizable) glfwSetFramebufferSizeCallback(this->window, framebuffer_resize_callback);

    glfwSetWindowUserPointer(this->window, this);
    glfwSetKeyCallback(this->window, key_callback);
}

bool render_window::is_open() {
    return !glfwWindowShouldClose(this->window);
}

void render_window::update() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void render_window::key_press_callback(int key, int scancode, int action, int mods) {
    this->ev_handler.key_press_callback(this->window, key, scancode, action, mods);
}

render_window::~render_window() {
}