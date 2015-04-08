#include "model_material.hpp"
#include "game_exception.hpp"
#include "utility.hpp"
#include <assimp/scene.h>

namespace Library {

  std::map<TextureType, UINT> ModelMaterial::sTextureTypeMappings;

  ModelMaterial::ModelMaterial(Model& model) : model_(model) {
    InitializeTextureTypeMappings();
  }

  ModelMaterial::ModelMaterial(Model& model, aiMaterial* material) : model_(model) {
    InitializeTextureTypeMappings();

    aiString name;
    material->Get(AI_MATKEY_NAME, name);
    name_ = name.C_Str();

    for (TextureType texture_type = (TextureType)0; texture_type < TextureTypeEnd; texture_type = (TextureType)(texture_type + 1)) {
      aiTextureType mapped_texture_type = (aiTextureType)sTextureTypeMappings[texture_type];

      UINT texture_count = material->GetTextureCount(mapped_texture_type);
      if (texture_count > 0) {
        std::vector<std::wstring>* textures = new std::vector<std::wstring>();
        textures_.insert(std::pair<TextureType, std::vector<std::wstring>*>(texture_type, textures));

        textures->reserve(texture_count);
        for (UINT texture_index = 0; texture_index < texture_count; texture_index++) {
          aiString path;
          if (material->GetTexture(mapped_texture_type, texture_index, &path)) {
            std::wstring wPath;
            Utility::ToWideString(path.C_Str(), wPath);
            textures->push_back(wPath);
          }
        }
      }
    }
  }

  ModelMaterial::~ModelMaterial() {
    for (auto textures : textures_)
      DeleteObject(textures.second);
  }

  void ModelMaterial::InitializeTextureTypeMappings() {
    if (sTextureTypeMappings.size() != TextureTypeEnd) {
      sTextureTypeMappings[TextureTypeDiffuse] = aiTextureType_DIFFUSE;
      sTextureTypeMappings[TextureTypeSpecularMap] = aiTextureType_SPECULAR;
      sTextureTypeMappings[TextureTypeAmbient] = aiTextureType_AMBIENT;
      sTextureTypeMappings[TextureTypeHeightMap] = aiTextureType_HEIGHT;
      sTextureTypeMappings[TextureTypeNormalMap] = aiTextureType_NORMALS;
      sTextureTypeMappings[TextureTypeSpecularPowerMap] = aiTextureType_SHININESS;
      sTextureTypeMappings[TextureTypeDisplacementMap] = aiTextureType_DISPLACEMENT;
      sTextureTypeMappings[TextureTypeLightMap] = aiTextureType_LIGHTMAP;
    }
  }

} // namespace Library