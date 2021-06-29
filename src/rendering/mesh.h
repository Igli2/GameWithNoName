#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <cstddef>

#include "buffer.h"
#include "vao.h"

namespace rendering {
    class mesh {
        private:
            size_t indices_count;

            vao va;

            std::vector<buffer> buffers;
        public:
            mesh();
            mesh(mesh&& other);
            mesh(const mesh& other) = delete;
            void draw();
            ~mesh();

            mesh& operator=(mesh&& other);
            mesh& operator=(const mesh& other) = delete;

            static mesh create(const GLenum draw_type, const size_t dimensions,
                               const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<float>& texture_coords = {});
    };   
}