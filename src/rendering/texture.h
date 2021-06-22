#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace rendering {
    class texture {
        private:
            unsigned int id;
        public:
            texture();
            texture(texture&& other);
            void use();
            texture(const texture& other) = delete;
            ~texture();

            texture& operator=(texture&& other);
            texture& operator=(const texture& other) = delete;

            static texture load_from_file(const std::string& filepath, const GLint min_filter, const GLint mag_filter,
                                          const GLint tex_wrap_s, const GLint tex_wrap_t, const GLint format);
    };    
}