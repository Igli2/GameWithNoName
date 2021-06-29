#include "mesh.h"

#include <utility>

using namespace rendering;

mesh::mesh() : va{}, buffers{}, indices_count(0) {
}

mesh::mesh(mesh&& other) {
    this->va = std::move(other.va);
    this->buffers = std::move(other.buffers);
    this->indices_count = other.indices_count;
    other.indices_count = 0;
}

void mesh::draw() {
    this->va.bind();

    glDrawElements(GL_TRIANGLES, this->indices_count, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}

bool mesh::set_data(const size_t i, buffer& buf, const size_t size, const GLenum type, const GLboolean normalized, const size_t stride, const size_t offset) {
    if(i == 0 || buf.get_type() != GL_ARRAY_BUFFER) return false;

    this->buffers.push_back(std::move(buf));
    this->va.set_vertex_attrib(this->buffers[this->buffers.size() - 1], i, size, type, normalized, stride, offset);

    return true;
}

mesh::~mesh() {
}

mesh& mesh::operator=(mesh&& other) {
    this->va = std::move(other.va);
    this->buffers = std::move(other.buffers);
    this->indices_count = other.indices_count;
    other.indices_count = 0;

    return *this;
}

//static
mesh mesh::create(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices, const std::vector<unsigned int>& indices) {
    mesh m{};

    m.buffers.push_back(buffer::create(vertices.size() * sizeof(float), &vertices[0], GL_ARRAY_BUFFER, draw_type));
    m.va.set_vertex_attrib(m.buffers[0], 0, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), 0);

    m.buffers.push_back(buffer::create(indices.size() * sizeof(unsigned int), &indices[0], GL_ELEMENT_ARRAY_BUFFER, draw_type));
    m.va.set_element_buffer(m.buffers[1]);

    m.indices_count = indices.size();

    return m;
}