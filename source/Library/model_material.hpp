#pragma once

#include "common.hpp"

struct aiMaterial;

namespace Library {

  enum TextureType {
    TextureTypeDiffuse = 0, 
    TextureTypeSpecularMap,
    TextureTypeAmbient,
    TextureTypeEmssive,
    TextureTypeHeightMap,
    TextureTypeNormalMap,
    TextureTypeSpecularPowerMap,
    TextureTypeDisplacementMap,
    TextureTypeLightMap,
    TextureTypeEnd
  };

  class ModelMaterial {
    friend class Model;

  public:
    ModelMaterial() = delete;
    ModelMaterial(Model& model);
    ModelMaterial(const ModelMaterial&) = delete;

    ModelMaterial& operator=(const ModelMaterial&) = delete;
    ~ModelMaterial();

    Model& GetModel() { return model_; }
    const std::string& Name() const { return name_; }
    const std::map<TextureType, std::vector<std::wstring>*> Textures() const { return textures_; }

  private:
    static void InitializeTextureTypeMappings();
    static std::map<TextureType, UINT> sTextureTypeMappings;

    ModelMaterial(Model& model, aiMaterial* material);

    Model& model_;
    std::string name_;
    std::map<TextureType, std::vector<std::wstring>*> textures_;
  }; // class ModelMaterial

} // namespace Library