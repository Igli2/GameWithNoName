#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstddef>

namespace rendering {
    class buffer {
        private:
            unsigned int id;
            GLenum type;

            void delete_data();
        public:
            buffer();
            buffer(const buffer& other) = delete;
            buffer(buffer&& other);
            void bind();
            bool empty();
            const GLenum get_type();
            //unsigned int get();
            unsigned int release();
            ~buffer();

            buffer& operator=(const buffer& other) = delete;
            buffer& operator=(buffer&& other);

            static buffer create(const size_t data_size, const void* data, const GLenum type, const GLenum usage);
    };
}