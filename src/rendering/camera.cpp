#include "camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include "shader_constants.h"

using namespace rendering;

camera::camera(const render_mode initial_mode) : view_mat{1.0f}, projection_2D{1.0f}, projection_3D{1.0f}, mode{initial_mode} {
}

render_mode camera::get_current_render_mode() {
    return this->mode;
}
void camera::set_render_mode(const render_mode mode) {
    if(this->get_current_render_mode() != mode) {
        this->mode = mode;
        this->update_render_perspective();
    }
}
void camera::set_view_matrix(const glm::mat4& view_mat) {
    this->view_mat = view_mat;
    this->update_render_perspective();
}
void camera::set_2D_projection_matrix(const glm::mat4& proj_mat) {
    this->projection_2D = proj_mat;
    this->update_render_perspective();
}
void camera::set_3D_projection_matrix(const glm::mat4& proj_mat) {
    this->projection_3D = proj_mat;
    this->update_render_perspective();
}

void camera::update_render_perspective() {
    if(this->mode == render_mode::RENDER_2D) {
        this->update_2D_perspective();
    } else {
        this->update_3D_perspective();
    }
}

camera::~camera() {
}

//private
void camera::update_3D_perspective() {
    glEnable(GL_DEPTH_TEST);
    glUniformMatrix4fv(shader_const::PROJECTION_MAT_LOCATION, 1, GL_FALSE, glm::value_ptr(this->projection_3D));
	glUniformMatrix4fv(shader_const::VIEW_MAT_LOCATION, 1, GL_FALSE, glm::value_ptr(this->view_mat));
}

void camera::update_2D_perspective() {
    glDisable(GL_DEPTH_TEST);
    glUniformMatrix4fv(shader_const::PROJECTION_MAT_LOCATION, 1, GL_FALSE, glm::value_ptr(this->projection_2D));
	glUniformMatrix4fv(shader_const::VIEW_MAT_LOCATION, 1, GL_FALSE, glm::value_ptr(glm::mat4{1.0f}));
}