#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <cstddef>

namespace rendering {
    class mesh {
        private:
            size_t indices_count;

            unsigned int vao;
            unsigned int vbo;
            unsigned int ebo;

            std::vector<unsigned int> vertex_attributes;
        public:
            mesh();
            mesh(mesh&& other);
            mesh(const mesh& other) = delete;
            void set_float_vertex_attribute(const std::vector<float>& values, const GLint index, const GLint size, const GLenum draw_type);
            void draw();
            ~mesh();

            mesh& operator=(mesh&& other);
            mesh& operator=(const mesh& other) = delete;

            static mesh create(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const GLenum draw_type);
    };   
}