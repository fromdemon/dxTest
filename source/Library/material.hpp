#pragma once

#include "common.hpp"
#include "effect.hpp"

namespace Library {

  class Model;
  class Mesh;

  class Material : public RTTI {
    RTTI_DECLARATIONS(Material, RTTI)

  public:
    Material() = default;
    Material(const std::string& default_technique_name);
    Material(const Material&) = delete;

    Material& operator=(const Material&) = delete;
    virtual ~Material();

    Variable* operator[](const std::string& variable_name);
    Effect* GetEffect() const { return effect_; }
    Technique* CurrentTechnique() const { return current_technique_; }
    void SetCurrentTechnique(Technique* current_technique);
    const std::map<Pass*, ID3D11InputLayout*>& InputLayout() const { return input_layout_; }
    
    virtual void Initialize(Effect* effect);
    virtual void CreateVertexBuffer(ID3D11Device* device, const Model& model, std::vector<ID3D11Buffer*>& vertex_buffer) const;
    virtual void CreateVertexBuffer(ID3D11Device* device, const Mesh& mesh, ID3D11Buffer** vertex_buffer) const = 0;
    virtual UINT VertexSize() const = 0;

  protected:
    virtual void CreateInputLayout(const std::string& technique_name, const std::string& pass_name, D3D11_INPUT_ELEMENT_DESC* input_element_desctiptions, UINT input_element_desctiption_count);
    
    Effect* effect_ = nullptr;
    Technique* current_technique_ = nullptr;
    std::string default_technique_name_;
    std::map<Pass*, ID3D11InputLayout*> input_layout_;
  }; // class Material

#define MATERIAL_VARIABLE_DECLARATION(variable_name) \
  public:                                            \
    Variable& variable_name() const;                 \
  private:                                           \
    Variable *m ## variable_name;

#define MATERIAL_VARIABLE_DEFINITIONS(variable_name) \
  Variable& Material::variable_name() const {        \
    return *m ## variable_name;                  \
    }

#define MATERIAL_VARIABLE_INITIALIZATION(variable_name) m ## variable_name(NULL)

#define MATERIAL_VARIABLE_RETIEVE(variable_name)     \
  m ## variable_name = effect_->VariablesByName().at(#variable_name);


} // namespace Library