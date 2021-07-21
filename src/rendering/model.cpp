#include "model.h"

#include <stdexcept>
#include <cstddef>
#include <utility>

using namespace rendering;

model::model() : model_meshes{} {
}

model::model(model&& other) {
    *this = std::move(other);
}

void model::draw(const glm::mat4& transform) {
    for(mesh& m : this->model_meshes) m.draw(transform);
}

model::~model() {
}

model& model::operator=(model&& other) {
    this->model_meshes = std::move(other.model_meshes);

    return *this;
}

//static methods
model model::load_from_file(const std::string& filepath) {
    Assimp::Importer importer;
    const aiScene* assimp_model = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

    if(!assimp_model || assimp_model->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !assimp_model->mRootNode) 
        throw std::runtime_error("Error on loading model with assimp: " + std::string(importer.GetErrorString()));

    model loaded_model{};
    loaded_model.add_meshes_from_node(assimp_model->mRootNode, assimp_model);

    return loaded_model;
}

//private
void model::add_meshes_from_node(const aiNode* assimp_node, const aiScene* assimp_model) {
    for(size_t node_mesh = 0; node_mesh < assimp_node->mNumMeshes; node_mesh++) {
        this->model_meshes.push_back(mesh::from_assimp_mesh(assimp_model->mMeshes[assimp_node->mMeshes[node_mesh]]));
    }

    for(size_t child = 0; child < assimp_node->mNumChildren; child++) {
        this->add_meshes_from_node(assimp_node->mChildren[child], assimp_model);
    }
}