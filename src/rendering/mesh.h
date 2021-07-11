#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <vector>
#include <cstddef>

#include "buffer.h"
#include "vao.h"
#include "vec.h"

namespace rendering {
    class mesh {
        private:
            size_t indices_count;
            
            bool has_texture;
            bool use_texture;

            bool has_color;
            bool use_color;

            vao data;

            std::vector<buffer> buffers;

            void set_texture_coords(const GLenum draw_type, const std::vector<float>& texture_coords);
            void set_color(const GLenum draw_type, const std::vector<float>& color);
        public:
            mesh();
            mesh(mesh&& other);
            mesh(const mesh& other) = delete;
            void draw(const glm::mat4& transform = glm::mat4{1.0f});
            void set_texture_usage(const bool state);
            void set_color_usage(const bool state);
            bool get_texture_usage();
            bool get_color_usage();
            ~mesh();

            mesh& operator=(mesh&& other);
            mesh& operator=(const mesh& other) = delete;

            static mesh create(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices, const std::vector<unsigned int>& indices);
            static mesh create_with_texture(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices,
                               const std::vector<unsigned int>& indices, const std::vector<float>& texture_coords);
            static mesh create_with_color(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices,
                               const std::vector<unsigned int>& indices, const std::vector<float>& color);
            static mesh create_with_texture_and_color(const GLenum draw_type, const size_t dimensions, const std::vector<float>& vertices,
                               const std::vector<unsigned int>& indices, const std::vector<float>& texture_coords, const std::vector<float>& color);
    };   
}