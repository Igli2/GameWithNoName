#include "mesh.h"

using namespace rendering;

mesh::mesh() : ebo(0), vao(0), vbo(0), indices_count(0) {
}

mesh::mesh(mesh&& other) {
    this->ebo = other.ebo;
    other.ebo = 0;
    this->vao = other.vao;
    other.vao = 0;
    this->vbo = other.vbo;
    other.vbo = 0;

    this->indices_count = other.indices_count;
}

unsigned int mesh::get_vao() {
    return this->vao;
}

void mesh::draw() {
    glBindVertexArray(this->vao);

    glDrawElements(GL_TRIANGLES, this->indices_count, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

mesh::~mesh() {
    if(this->ebo != 0) glDeleteBuffers(1, &this->ebo);
    if(this->vao != 0) glDeleteVertexArrays(1, &this->vao);
    if(this->vbo != 0) glDeleteBuffers(1, &this->vbo);
}

mesh& mesh::operator=(mesh&& other) {
    this->ebo = other.ebo;
    other.ebo = 0;
    this->vao = other.vao;
    other.vao = 0;
    this->vbo = other.vbo;
    other.vbo = 0;

    this->indices_count = other.indices_count;

    return *this;
}

//static
mesh mesh::create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const GLenum draw_type) {
    mesh m{};

    m.indices_count = indices.size();

    glGenVertexArrays(1, &m.vao);
    glBindVertexArray(m.vao);

    glGenBuffers(1, &m.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], draw_type);

    glGenBuffers(1, &m.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], draw_type);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    
    return std::move(m);
}