#include "buffer.h"

using namespace rendering;

buffer::buffer(buffer&& other) {
    this->id = other.release();
}

void buffer::delete_data() {
    if(this->id != 0) {
        glDeleteBuffers(1, &this->id);
        this->id = 0;
    }
}

/*unsigned int buffer::get() {
    return this->id;
}*/

void buffer::bind() {
    glBindBuffer(this->type, this->id);
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
    this->id = other.release();

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