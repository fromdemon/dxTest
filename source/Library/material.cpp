#include "material.hpp"
#include "game_exception.hpp"
#include "model.hpp"

namespace Library {

  RTTI_DEFINITIONS(Material)

  Material::Material(const std::string& default_technique_name) : default_technique_name_(default_technique_name) {
  }

  Material::~Material() {
    for (std::pair<Pass*, ID3D11InputLayout*> input_layout : input_layout_)
      ReleaseObject(input_layout.second);
  }
  

  Variable* Material::operator[](const std::string& variable_name) {
    const std::map<std::string, Variable*>& variables = effect_->VariablesByName();
    Variable* found_variable = nullptr;
    std::map<std::string, Variable*>::const_iterator found = variables.find(variable_name);
    if (found != variables.end())
      found_variable = found->second;

    return found_variable;
  }

  void Material::Initialize(Effect* effect) {
    effect_ = effect;
    assert(effect_ != nullptr);

    Technique* default_technique = nullptr;
    assert(effect->Techniques().size() > 0);
    if (default_technique_name_.empty() == false) {
      default_technique = effect->TechniquesByName().at(default_technique_name_);
      assert(default_technique != nullptr);
    }
    else {
      default_technique = effect_->Techniques().at(0);
    }
    SetCurrentTechnique(default_technique);
  }

  void Material::CreateVertexBuffer(ID3D11Device* direct3d_device, const Model& model, std::vector<ID3D11Buffer*>& vertex_buffers) const {
    vertex_buffers.reserve(model.Meshes().size());
    for (Mesh* mesh : model.Meshes()) {
      ID3D11Buffer* vertex_buffer;
      CreateVertexBuffer(direct3d_device, *mesh, &vertex_buffer);
      vertex_buffers.push_back(vertex_buffer);
    }
  }

    void Material::CreateInputLayout(const std::string& technique_name, const std::string& pass_name, D3D11_INPUT_ELEMENT_DESC* input_element_descriptions, UINT input_element_description_count) {
      Technique* technique = effect_->TechniquesByName().at(technique_name);
      assert(technique != nullptr);

      Pass* pass = technique->PassesByName().at(pass_name);
      assert(pass != nullptr);

      ID3D11InputLayout* input_layout;
      pass->CreateInputLayout(input_element_descriptions, input_element_description_count, &input_layout);
      input_layout_.insert(std::pair<Pass*, ID3D11InputLayout*>(pass, input_layout));
  }
} // namespace Library