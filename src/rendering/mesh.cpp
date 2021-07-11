#include "mesh.h"

#include <glm/gtc/type_ptr.hpp>

#include <utility>

#include "shader_constants.h"

using namespace rendering;

mesh::mesh() : data{}, buffers{}, indices_count(0), has_texture{false}, use_texture{false}, has_color{false}, use_color{false} {
}

mesh::mesh(mesh&& other) {
    *this = std::move(other);
}

void mesh::draw(const glm::mat4& transform) {
    glUniform1i(shader_const::USE_TEXTURE_LOCATION, this->use_texture);
    glUniform1i(shader_const::USE_COLOR_LOCATION, this->use_color);
    glUniformMatrix4fv(shader_const::TRANSFORM_MAT_LOCATION, 1, GL_FALSE, glm::value_ptr(transform));

    this->data.bind();

    glDrawElements(GL_TRIANGLES, this->indices_count, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

void mesh::set_texture_usage(const bool state) {
    this->use_texture = state && this->has_texture;
}

void mesh::set_color_usage(const bool state) {
    this->use_color = state && this->has_color;
}

bool mesh::get_texture_usage() {
    return this->use_texture;
}

bool mesh::get_color_usage() {
    return this->use_color;
}

mesh::~mesh() {
}

mesh& mesh::operator=(mesh&& other) {
    this->data = std::move(other.data);
    this->buffers = std::move(other.buffers);
    this->indices_count = other.indices_count;

    this->has_texture = other.has_texture;
    this->use_texture = other.use_texture;

    this->has_color = other.has_color;
    this->use_color = other.use_color;
    other.indices_count = 0;

    return *this;
}

//static
mesh mesh::create(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    mesh m{};

    m.buffers.push_back(buffer::create(vertices.size() * sizeof(float), &vertices[0], GL_ARRAY_BUFFER, draw_type));
    m.data.set_vertex_attrib(m.buffers.back(), 0, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), 0);

    m.buffers.push_back(buffer::create(indices.size() * sizeof(unsigned int), &indices[0], GL_ELEMENT_ARRAY_BUFFER, draw_type));
    m.data.set_element_buffer(m.buffers.back());

    m.indices_count = indices.size();

    return m;
}

mesh mesh::create_with_texture(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices,
                    const std::vector<unsigned int>& indices, const std::vector<float>& texture_coords) {
    mesh m = mesh::create(draw_type, dimensions, vertices, indices);

    m.set_texture_coords(draw_type, texture_coords);

    return m;
}

mesh mesh::create_with_color(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices,
                    const std::vector<unsigned int>& indices, const std::vector<float>& color) {
    mesh m = mesh::create(draw_type, dimensions, vertices, indices);

    m.set_color(draw_type, color);

    return m;
}

mesh mesh::create_with_texture_and_color(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices,
                    const std::vector<unsigned int>& indices, const std::vector<float>& texture_coords, const std::vector<float>& color) {
    mesh m = mesh::create(draw_type, dimensions, vertices, indices);

    m.set_texture_coords(draw_type, texture_coords);
    m.set_color(draw_type, color);

    return m;
}

//private
void mesh::set_texture_coords(const GLenum draw_type, const std::vector<float>& texture_coords) {
    this->buffers.push_back(buffer::create(texture_coords.size() * sizeof(float), &texture_coords[0], GL_ARRAY_BUFFER, draw_type));
    this->data.set_vertex_attrib(this->buffers.back(), 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

    this->has_texture = true;
    this->use_texture = true;
}

void mesh::set_color(const GLenum draw_type, const std::vector<float>& color) {
    this->buffers.push_back(buffer::create(color.size() * sizeof(float), &color[0], GL_ARRAY_BUFFER, draw_type));
    this->data.set_vertex_attrib(this->buffers.back(), 2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

    this->has_color = true;
    this->use_color = true;
}