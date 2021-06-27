#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>

namespace rendering {
    class buffer {
        private:
            unsigned int id;
            GLenum type;

            buffer();
        public:
            buffer(const buffer& other) = delete;
            buffer(buffer&& other);
            void delete_data();
            void bind();
            //unsigned int get();
            unsigned int release();
            ~buffer();

            buffer& operator=(const buffer& other) = delete;
            buffer& operator=(buffer&& other);

            static buffer create(const size_t data_size, const void* data, const GLenum type, const GLenum usage);
    };
}