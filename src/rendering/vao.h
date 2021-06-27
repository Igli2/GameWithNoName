#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>

#include "buffer.h"

namespace rendering {
    class vao {
    private:
        unsigned int id;

        void delete_data();
    public:
        vao();
        vao(const vao& other) = delete;
        vao(vao&& other);
        unsigned int release();
        void set_element_buffer(buffer& ebo);
        void set_vertex_attrib(buffer& buf, const unsigned int va,
                               const size_t size, const GLenum type, const GLboolean normalized, const size_t stride, const size_t offset);
        void disable_vertex_attrib(const unsigned int va);
        void enable_vertex_attrib(const unsigned int va);
        void bind();
        ~vao();

        vao& operator=(const vao& other) = delete;
        vao& operator=(vao&& other);
    };    
}