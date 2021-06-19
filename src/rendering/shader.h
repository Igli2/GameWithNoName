#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <istream>

namespace rendering {
    class shader_program;

    class shader {
        private:
            int id; 

            int get() const;
        public:
            shader();
            shader(shader&& other);
            shader(const shader& other) = delete;
            ~shader();

            shader& operator=(shader&& other);
            shader& operator=(const shader& other) = delete;

            static shader from_stream(std::istream& stream, const GLint shader_type);

        friend shader_program;
    }; 

    class shader_program {
        private:
            int id;
        public:
            shader_program();
            shader_program(const std::vector<shader>& shaders);
            shader_program(shader_program&& other);
            shader_program(const shader_program& other) = delete;
            void use() const;
            ~shader_program();

            shader_program& operator=(shader_program&& other);
            shader_program& operator=(const shader_program& other) = delete;
    };    
}