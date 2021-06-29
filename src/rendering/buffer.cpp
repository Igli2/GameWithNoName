#include "buffer.h"

//#include <iostream>
#include <utility>

using namespace rendering;

buffer::buffer(buffer&& other) {
    this->delete_data();
    this->id = other.release();
    this->type = other.type;
}

/*unsigned int buffer::get() {
    return this->id;
}*/

void buffer::bind() {
    glBindBuffer(this->type, this->id);
}

void buffer::unbind() {
    glBindBuffer(this->type, 0);
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

//private
buffer::buffer() : id{0}, type{} {
    glGenBuffers(1, &this->id);
}

void buffer::delete_data() {
    if(this->id != 0) {
        glDeleteBuffers(1, &this->id);
        this->id = 0;
    }
}