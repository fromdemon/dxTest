#include "mesh.hpp"

#include "game.hpp"
#include <assimp/scene.h>

namespace Library {

  Mesh::Mesh(Model& model, aiMesh& mesh) : model_(model), name_(mesh.mName.C_Str()) {

  }

} // namespace Library