#include "vao.h"

using namespace rendering;

vao::vao() {
    glGenVertexArrays(1, &this->id);
}

vao::vao(vao&& other) {
    this->delete_data();
    this->id = other.release();
}

unsigned int vao::release() {
    const unsigned int ret = this->id;
    this->id = 0;

    return ret;
}

void vao::set_element_buffer(buffer& ebo) {
    this->bind();
    ebo.bind();

    glBindVertexArray(0);
    ebo.unbind();
}

void vao::set_vertex_attrib(buffer& buf, const unsigned int va,
                            const size_t size, const GLenum type, const GLboolean normalized, const size_t stride, const size_t offset) {
    this->bind();
    buf.bind();

    glVertexAttribPointer(va, size, type, normalized, stride, (void*)offset);

    glBindVertexArray(0);
    buf.unbind();

    this->enable_vertex_attrib(va);
}

void vao::disable_vertex_attrib(const unsigned int va) {
    this->bind();

    glDisableVertexAttribArray(va);

    glBindVertexArray(0);
}

void vao::enable_vertex_attrib(const unsigned int va) {
    this->bind();

    glEnableVertexAttribArray(va);

    glBindVertexArray(0);
}

void vao::bind() {
    glBindVertexArray(this->id);
}

vao::~vao() {
    this->delete_data();
}

vao& vao::operator=(vao&& other) {
    this->delete_data();
    this->id = other.release();

    return *this;
}

//private
void vao::delete_data() {
    if(this->id != 0) {
        glDeleteVertexArrays(1, &this->id);
        this->id = 0;
    }
}
