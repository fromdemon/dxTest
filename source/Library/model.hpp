#pragma once

#include "common.hpp"

namespace Library {

  class Game;
  class Mesh;
  class ModelMaterial;

  class Model {
  public:
    Model() = delete;
    Model(Game& game, const std::string& filename, bool flipUVs = false);
    Model(const Model&) = delete;
    ~Model();

    Model& operator=(const Model&) = delete;

    Game& GetGame() { return game_; }
    bool HasMeshes() const { return (meshes_.size() > 0); }
    bool HasMaterials() const { return (materials_.size() > 0); }

    const std::vector<Mesh*>& Meshes() const { return meshes_; }
    const std::vector<ModelMaterial*>& Materials() const { return materials_; }

  private:
    Game& game_;
    std::vector<Mesh*> meshes_;
    std::vector<ModelMaterial*> materials_;
  }; // class Model

} // namespace Library