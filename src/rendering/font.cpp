#include "font.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

#include <utility>
#include <stdexcept>
#include <freetype2/ft2build.h>
#include FT_FREETYPE_H

#include "shader_constants.h"

using namespace rendering;

const std::vector<float> TEXTURE_COORDS {{
    0.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f,
    1.0f, 0.0f
}};

const std::vector<unsigned int> RECT_INDICES {{
    0, 1, 3,
    1, 2, 3
}};

//helper functions
character load_char(FT_Face& font_face, const char to_load);

character load_char(FT_Face& font_face, const char to_load) {
    if(FT_Load_Char(font_face, to_load, FT_LOAD_RENDER)) 
        throw std::runtime_error("Unable to load char '" + std::string(1, to_load) + "'(code: " + std::to_string(to_load) + "!");

    character char_data{};

    char_data.size = vec2<size_t>{font_face->glyph->bitmap.width, font_face->glyph->bitmap.rows};
    char_data.bearing = vec2<int>{font_face->glyph->bitmap_left, font_face->glyph->bitmap_top};

    char_data.advance_offset = vec2<int>{(int)font_face->glyph->advance.x >> 6, 0};

    char_data.char_texture = texture::load(font_face->glyph->bitmap.buffer, char_data.size.x, char_data.size.y,
                                           GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_RED);

    font_face->glyph->bitmap.buffer;

    return char_data;
}

font::font() : rect_vao{}, rect_vert{}, rect_tex_coords{}, rect_ind{} {
    this->rect_vert = buffer::create(8 * sizeof(float), nullptr, GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    this->rect_tex_coords = buffer::create(TEXTURE_COORDS.size() * sizeof(float), &TEXTURE_COORDS[0], GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    this->rect_ind = buffer::create(RECT_INDICES.size() * sizeof(unsigned int), &RECT_INDICES[0], GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    this->rect_vao.set_vertex_attrib(this->rect_vert, 0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    this->rect_vao.set_vertex_attrib(this->rect_tex_coords, 1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    this->rect_vao.set_element_buffer(this->rect_ind);
}

font::font(font&& other) {
    *this = std::move(other);
}

void font::draw_string(const std::string& str, const float scale, const vec4<float>& color, const glm::mat4& transform) {
    glUniform4f(shader_const::FONT_COLOR_LOCATION, color.x, color.y, color.z, color.w);
    glUniformMatrix4fv(shader_const::TRANSFORM_MAT_LOCATION, 1, GL_FALSE, glm::value_ptr(transform));

    this->rect_vao.bind();

    float x_off = 0;
    for(const char to_draw : str) {
        character& char_data = this->character_textures[to_draw];
        
        std::vector<float> rect_bounds = font::get_rect_bounds(char_data, x_off, scale);

        char_data.char_texture.use();
        this->rect_vert.set(0, rect_bounds.size() * sizeof(float), &rect_bounds[0]);
        
        glDrawElements(GL_TRIANGLES, RECT_INDICES.size(), GL_UNSIGNED_INT, nullptr);

        x_off += char_data.advance_offset.x * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

vec2<float> font::get_string_render_bounds(const std::string& str, const float scale) {
    vec2<float> bounds{};

    for(size_t c = 0; c < str.size(); c++) {
        const character& char_data = this->character_textures[str[c]];

        float height = char_data.size.y * scale;
        if(height > bounds.y) bounds.y = height;

        if(c == str.size() - 1) {
            bounds.x += char_data.size.x * scale;
        } else {
            bounds.x += char_data.advance_offset.x * scale;
        }
    }

    return bounds;
}

font::~font() {
}

font& font::operator=(font&& other) {
    this->character_textures = std::move(other.character_textures);
    this->rect_vert = std::move(other.rect_vert);
    this->rect_tex_coords = std::move(other.rect_tex_coords);
    this->rect_ind = std::move(other.rect_ind);
    this->rect_vao = std::move(other.rect_vao);

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

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(unsigned char to_load = 0; to_load < 128; to_load++) {
        f.character_textures.push_back(load_char(font_face, to_load));
    }

    FT_Done_Face(font_face);
    FT_Done_FreeType(ft_lib);

    return f;
}

//private
std::vector<float> font::get_rect_bounds(const character& char_data, const float x_off, const float scale) {
    float width = char_data.size.x * scale;
    float height = char_data.size.y * scale;

    float pos_x = x_off + char_data.bearing.x * scale;
    float pos_y = char_data.bearing.y * scale - height;

    return std::vector<float>{
        pos_x, pos_y + height,
        pos_x, pos_y,
        pos_x + width, pos_y,
        pos_x + width, pos_y + height
    };
}