#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "mesh.h"

namespace rendering {
    class model {
        private:
            std::vector<mesh> model_meshes;
        public:
            model();
            void draw(const glm::mat4& transform = glm::mat4{1.0f});
            ~model();

            static model load_from_file(const std::string& filepath);
        };    
}