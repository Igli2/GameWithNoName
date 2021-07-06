#include "buffer.h"

//#include <iostream>
#include <utility>

using namespace rendering;

buffer::buffer() : type{} {
    glGenBuffers(1, &this->id);
}

buffer::buffer(buffer&& other) {
    this->delete_data();
    this->id = other.release();
    this->type = other.type;
}

void buffer::bind() {
    glBindBuffer(this->type, this->id);
}

void buffer::set(const size_t start, const size_t size, const void* data) {
    this->bind();
    glBufferSubData(GL_ARRAY_BUFFER, start, size, data);
    glBindBuffer(this->type, 0);
}

bool buffer::empty() {
    return this->id == 0;
}

const GLenum buffer::get_type() {
    return this->type;
}

unsigned int buffer::release() {
    const unsigned int ret = this->id;
    this->id = 0;

    return ret;
}

buffer::~buffer() {
    this->delete_data();
}

buffer& buffer::operator=(buffer&& other) {
    this->delete_data();
    this->id = other.release();
    this->type = other.type;

    return *this;
}

//static
buffer buffer::create(const size_t data_size, const void* data, const GLenum type, const GLenum usage) {
    buffer b{};
    b.type = type;

    glBindBuffer(type, b.id);
    glBufferData(type, data_size, data, usage);
    glBindBuffer(type, 0);

    return b;
}

void buffer::delete_data() {
    if(this->id != 0) {
        glDeleteBuffers(1, &this->id);
        this->id = 0;
    }
}