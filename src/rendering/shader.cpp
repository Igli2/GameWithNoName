#include "shader.h"

#include <stdexcept>
#include <string>
#include <utility>

using namespace rendering;

shader::shader() : id(0) {

}

shader::shader(shader&& other) {
    this->id = other.id;
    other.id = 0;
}

shader::~shader() {
    if(this->id != 0) glDeleteShader(this->id);
}

shader& shader::operator=(shader&& other) {
    this->id = other.id;
    other.id = 0;

    return *this;
}

//private
int shader::get() const {
    return this->id;
}

//static
shader shader::from_stream(std::istream& stream, const GLint shader_type) {
    shader s{};
	s.id = glCreateShader(shader_type);

    std::streampos start = stream.tellg();
    stream.seekg(0, std::ios::end);
    std::streampos end = stream.tellg();
    stream.seekg(start, std::ios::beg);

    std::string source(end - start, '\0');

    stream.read(&source[0], end - start);

    const char * const s_begin = &source[0];
	glShaderSource(s.id, 1, &s_begin, nullptr);
	glCompileShader(s.id);

	// shader errors
	int success;
	glGetShaderiv(s.id, GL_COMPILE_STATUS, &success);

	if(!success) {
        char log[512];
		glGetShaderInfoLog(s.id, 512, nullptr, log);
        throw std::runtime_error("**SHADER COMPILATION ERROR**\n" + std::string(log));
	}

    return std::move(s);
}



shader_program::shader_program() : id(0) {

}

shader_program::shader_program(const std::vector<shader>& shaders) {
    this->id = glCreateProgram();

    for(const shader& s : shaders) {
        glAttachShader(this->id, s.get());        
    }

    glLinkProgram(this->id);

    int success;
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if(!success) {
        char log[512];
        glGetProgramInfoLog(this->id, 512, nullptr, log);
        throw std::runtime_error("**SHADER PROGRAM LINK ERROR**\n" + std::string(log));
    }
}

shader_program::shader_program(shader_program&& other) {
    this->id = other.id;
    other.id = 0;
}

void shader_program::use() const {
    glUseProgram(this->id);
}

shader_program::~shader_program() {
    if(this->id != 0) glDeleteProgram(this->id);
}

shader_program& shader_program::operator=(shader_program&& other) {
    this->id = other.id;
    other.id = 0;

    return *this;
}