#include "pass.hpp"
#include "game.hpp"
#include "game_exception.hpp"

namespace Library {

Pass::Pass(Game& game, Technique& technique, ID3DX11EffectPass* pass) : game_(game), technique_(technique), pass_(pass) {
  pass_->GetDesc(&pass_desc_);
  name_ = pass_desc_.Name;
}

void Pass::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* input_element_desc, UINT num_elements, ID3D11InputLayout** input_layout) {
  HRESULT hr = game_.Direct3DDevice()->CreateInputLayout(input_element_desc, num_elements, pass_desc_.pIAInputSignature, pass_desc_.IAInputSignatureSize, input_layout);
  if (FAILED(hr))
    throw GameException("ID3D11Device::CreateInputLayout() failed.", hr);
}

void Pass::Apply(UINT flags, ID3D11DeviceContext* context) {
  pass_->Apply(flags, context);
}

} // namespace Library
