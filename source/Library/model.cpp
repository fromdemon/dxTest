#include "model.hpp"
#include "game.hpp"
#include "game_exception.hpp"
#include "mesh.hpp"
#include "model_material.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Library {

  Model::Model(Game& game, const std::string& filename, bool flipUVs) : game_(game) {
    Assimp::Importer importer;

    UINT flags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_FlipWindingOrder;
    if (flipUVs)
      flags |= aiProcess_FlipUVs;

    const aiScene* scene = importer.ReadFile(filename, flags);
    if (scene == nullptr)
      throw GameException(importer.GetErrorString());

    if (scene->HasMaterials()) {
      for (UINT i = 0; i < scene->mNumMaterials; i++)
        materials_.push_back(new ModelMaterial(*this, scene->mMaterials[i]));
    }

    if (scene->HasMeshes()) {
      for (UINT i = 0; i < scene->mNumMeshes; i++) {
        ModelMaterial* material = (materials_.size() > i ? materials_.at(i) : nullptr);
        Mesh* mesh = new Mesh(*this, *(scene->mMeshes[i]));
        meshes_.push_back(mesh);
      }
    }
  }

  Model::~Model() {
    for (auto* mesh : meshes_)
      delete mesh;

    for (auto* material : materials_)
      delete material;
  }

} // namespace Library