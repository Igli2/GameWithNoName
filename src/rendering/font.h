#pragma once

#include <vector>
#include <string>
#include <cstddef>

#include "texture.h"
#include "vec.h"
#include "vao.h"
#include "buffer.h"

namespace rendering {
    struct character {
        texture char_texture;

        vec2<size_t> size;

        vec2<int> bearing;
        vec2<int> advance_offset;
    };

    class font {
        private:
            std::vector<character> character_textures;

            vao rect_vao;
            buffer rect_vert;
            buffer rect_tex_coords;
            buffer rect_ind;

            static std::vector<float> get_rect_bounds(const character& char_data, const float x_off, const float scale);
        public:
            font();
            font(font&& other);
            font(const font& other) = delete;
            void draw_string(const std::string& str, const float scale, const vec4<float>& color, const vec3<float>& draw_position = {});
            ~font();

            font& operator=(const font& other) = delete;
            font& operator=(font&& other);

            static font load_from_file(const std::string& filepath, const size_t font_size, const size_t face_index = 0);
    };    
}