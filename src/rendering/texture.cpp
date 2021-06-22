#include "texture.h"

#include <stdexcept>

#include <stb_image.h>

using namespace rendering;

texture::texture() : id(0) {
}

texture::texture(texture&& other) {
    this->id = other.id;
    other.id = 0;
}

void texture::use() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}

texture::~texture() {
    if(this->id != 0) glDeleteTextures(1, &this->id);
}

texture& texture::operator=(texture&& other) {
    this->id = other.id;
    other.id = 0;

    return *this;
}

//static
texture texture::load_from_file(const std::string& filepath, const GLint min_filter, const GLint mag_filter,
                                const GLint tex_wrap_s, const GLint tex_wrap_t, const GLint format) {
    int width, height, channels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

    if(!data) throw std::runtime_error("Unable to open image!");

    texture tex{};

    glGenTextures(1, &tex.id);
    glBindTexture(GL_TEXTURE_2D, tex.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, tex_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tex_wrap_t);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(data);

    return tex;
}