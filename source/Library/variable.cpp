#include "variable.hpp"
#include "game_exception.hpp"

namespace Library {

  Variable::Variable(Effect& effect, ID3DX11EffectVariable* variable) : effect_(effect), variable_(variable) {
    variable_->GetDesc(&variable_desc_);
    name_ = variable_desc_.Name;
    type_ = variable_->GetType();
    type_->GetDesc(&type_desc_);
  }

  Variable& Variable::operator<<(CXMMATRIX value) {
    ID3DX11EffectMatrixVariable* variable = variable_->AsMatrix();
    if (variable->IsValid() == false)
      throw GameException("Invalid effect variable cast.");

    variable->SetMatrix(reinterpret_cast<const float*>(&value));
    return *this;
  }

  Variable& Variable::operator<<(ID3D11ShaderResourceView* value) {
    ID3DX11EffectShaderResourceVariable* variable = variable_->AsShaderResource();
    if (variable->IsValid() == false)
      throw GameException("Invalid effect variable cast.");

    variable->SetResource(value);
    return *this;
  }

  Variable& Variable::operator<<(FXMVECTOR value) {
    ID3DX11EffectVectorVariable* variable = variable_->AsVector();
    if (variable->IsValid() == false)
      throw GameException("Invalid effect variable cast.");

    variable->SetFloatVector(reinterpret_cast<const float*>(&value));
    return *this;
  }

  Variable& Variable::operator<<(float value) {
    ID3DX11EffectScalarVariable* variable = variable_->AsScalar();
    if (variable->IsValid() == false)
      throw GameException("Invalid effect variable cast.");

    variable->SetFloat(value);
    return *this;
  }
} // namespace Library