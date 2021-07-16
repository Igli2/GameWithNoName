#include "render_window.h"

#include <stdexcept>

using namespace rendering;

//helper_functions
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    ((render_window*)glfwGetWindowUserPointer(window))->key_press_event(key, scancode, action, mods);
}

void mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
    ((render_window*)glfwGetWindowUserPointer(window))->mouse_move_event(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    ((render_window*)glfwGetWindowUserPointer(window))->mouse_button_event(button, action, mods);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    ((render_window*)glfwGetWindowUserPointer(window))->scroll_event(xoffset, yoffset);
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
    glfwSetKeyCallback(this->window, key_press_callback);
    glfwSetCursorPosCallback(this->window, mouse_move_callback);  
    glfwSetScrollCallback(this->window, scroll_callback);
    glfwSetMouseButtonCallback(this->window, mouse_button_callback);
}

bool render_window::is_open() {
    return !glfwWindowShouldClose(this->window);
}

void render_window::update() {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
}

void render_window::key_press_event(int key, int scancode, int action, int mods) {
    this->ev_handler.key_press_callback(this, key, scancode, action, mods);
}

void render_window::mouse_move_event(double xpos, double ypos) {
    this->ev_handler.mouse_move_callback(this, xpos, ypos);
}

void render_window::mouse_button_event(int button, int action, int mods) {
    this->ev_handler.mouse_button_callback(this, button, action, mods);
}

void render_window::scroll_event(double xoffset, double yoffset) {
    this->ev_handler.scroll_callback(this, xoffset, yoffset);
}

void render_window::get_mouse_position(double* x, double* y) {
    int width, height;
    glfwGetWindowSize(this->window, &width, &height);
    glfwGetCursorPos(this->window, x, y);
    *y = height - *y;
}

void render_window::get_window_size(int* width, int* height) {
    glfwGetWindowSize(this->window, width, height);
}

void render_window::close() {
    glfwSetWindowShouldClose(this->window, GL_TRUE);
}

render_window::~render_window() {
}