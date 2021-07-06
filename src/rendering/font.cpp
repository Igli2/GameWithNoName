#include "font.h"

#include <utility>
#include <stdexcept>
#include <freetype2/ft2build.h>
#include <freetype2/freetype/freetype.h>

using namespace rendering;

//helper functions
texture load_char(FT_Face& font_face, const char to_load);

texture load_char(FT_Face& font_face, const char to_load) {
    if(FT_Load_Char(font_face, to_load, FT_LOAD_RENDER)) 
        throw std::runtime_error("Unable to load char '" + std::string(1, to_load) + "'(code: " + std::to_string(to_load) + "!");

    

    return texture{};
}

font::font() {
}

font::font(font&& other) {
    *this = std::move(other);
}

font::~font() {
}

font& font::operator=(font&& other) {
    this->character_textures = std::move(other.character_textures);

    return *this;
}

//static
font font::load_from_file(const std::string& filepath, const size_t font_size, const size_t face_index) {
    font f{};

    FT_Library ft_lib;
    if(FT_Init_FreeType(&ft_lib)) throw std::runtime_error("Unable to initialize FreeType!");

    FT_Face font_face;
    if(FT_New_Face(ft_lib, filepath.c_str(), face_index, &font_face)) throw std::runtime_error("Unable to load font!");

    FT_Set_Pixel_Sizes(font_face, 0, font_size);

    for(char to_load = 0; to_load < 128; to_load++) {
        texture char_texture = load_char(font_face, to_load);
    }

    return f;
}