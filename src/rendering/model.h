#pragma once

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <vector>

#include "mesh.h"

namespace rendering {
    class model {
        private:
            std::vector<mesh> model_meshes;

            void add_meshes_from_node(const aiNode* assimp_node, const aiScene* assimp_model);
        public:
            model();
            model(model&& other);
            model(const model& other) = delete;
            void draw(const glm::mat4& transform = glm::mat4{1.0f});
            ~model();

            model& operator=(model&& other);
            model& operator=(const model& other) = delete;

            static model load_from_file(const std::string& filepath);
        };    
}