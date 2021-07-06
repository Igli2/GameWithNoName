#pragma once

#include <vector>
#include <string>
#include <cstddef>

#include "texture.h"
#include "vec.h"

namespace rendering {
    struct character {
        texture char_texture;

        size_t width;
        size_t height;
    };

    class font {
        private:
            std::vector<texture> character_textures;
        public:
            font();
            font(font&& other);
            font(const font& other) = delete;
            ~font();

            font& operator=(const font& other) = delete;
            font& operator=(font&& other);

            static font load_from_file(const std::string& filepath, const size_t font_size, const size_t face_index = 0);
    };    
}