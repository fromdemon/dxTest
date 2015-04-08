#pragma once

#include "common.hpp"

namespace Library {

  class Effect;

  class Variable {
  public:
    Variable() = delete;
    Variable(const Variable&) = delete;
    Variable& operator=(const Variable&) = delete;
    Variable(Effect& effect, ID3DX11EffectVariable* variable);

    Effect& GetEffect() { return effect_; }
    ID3DX11EffectVariable* GetVariable() const { return variable_; }
    const D3DX11_EFFECT_VARIABLE_DESC& VariableDesc() const { return variable_desc_; }
    ID3DX11EffectType* Type() const { return type_; }
    const D3DX11_EFFECT_TYPE_DESC TypeDesc() const { return type_desc_; }
    const std::string& Name() const { return name_; }

    Variable& operator<<(CXMMATRIX value);
    Variable& operator<<(ID3D11ShaderResourceView* value);
    Variable& operator<<(FXMVECTOR value);
    Variable& operator<<(float value);

  private:
    Effect& effect_;
    ID3DX11EffectVariable* variable_;
    D3DX11_EFFECT_VARIABLE_DESC variable_desc_;
    ID3DX11EffectType* type_ = nullptr;
    D3DX11_EFFECT_TYPE_DESC type_desc_;
    std::string name_;
  }; // class Variable

} // namespace Library