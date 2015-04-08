#pragma once

#include "common.hpp"

namespace Library {

  class Game;
  class Technique;

  class Pass {
  public:
    Pass() = delete;
    Pass(const Pass&) = delete;
    Pass& operator=(const Pass&) = delete;
    Pass(Game& game, Technique& technique, ID3DX11EffectPass* pass);

    Technique& GetTechnique() { return technique_; }
    ID3DX11EffectPass* GetPass() const { return pass_; }
    const D3DX11_PASS_DESC& PassDesc() const { return pass_desc_; }
    const std::string& Name() const { return name_; }

    void CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* input_element_desc, UINT num_elements, ID3D11InputLayout** input_layout);
    void Apply(UINT flags, ID3D11DeviceContext* context);

  private:
    Game& game_;
    Technique& technique_;
    ID3DX11EffectPass* pass_;
    D3DX11_PASS_DESC pass_desc_;
    std::string name_;
  }; // class Pass

} // namespace Library