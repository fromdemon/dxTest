#include "effect.hpp"
#include "game.hpp"
#include "game_exception.hpp"
#include "utility.hpp"
#include "D3Dcompiler.h"

namespace Library {

  Effect::Effect(Game& game) : game_(game) {
  }

  Effect::~Effect() {
    for (Technique* technique : techniques_)
      delete technique;

    for (Variable* variable : variables_)
      delete variable;

    variables_.clear();
    ReleaseObject(effect_);
  }

  void Effect::CompileEffectFromFile(ID3D11Device* direct3d_device, ID3DX11Effect** effect, const std::wstring& filename) {
    UINT shader_flags = 0;

#if defined(DEBUG) || defined (_DEGUG)
    shader_flags |= D3DCOMPILE_DEBUG;
    shader_flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

    ID3D10Blob* compiled_shader = nullptr;
    ID3D10Blob* error_messages = nullptr;
    HRESULT hr = D3DCompileFromFile(filename.c_str(), nullptr, nullptr, nullptr, "fx_5_0", shader_flags, 0, &compiled_shader, &error_messages);
    if (error_messages != nullptr) {
      GameException ex((char*)error_messages->GetBufferPointer(), hr);
      ReleaseObject(error_messages);
      throw ex;
    }

    if (FAILED(hr))
      throw GameException("D3DX11CompileFromFile() failed.", hr);

    hr = D3DX11CreateEffectFromMemory(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), NULL, direct3d_device, effect);
    if (FAILED(hr))
      throw GameException("D3DX11CreateEffectFromMemory() failed.", hr);

    ReleaseObject(compiled_shader);
  }

  void Effect::LoadCompiledEffect(ID3D11Device* direct3d_device, ID3DX11Effect** effect, const std::wstring& filename) {
    std::vector<char> compiled_shader;
    Utility::LoadBinaryFile(filename, compiled_shader);
    HRESULT hr = D3DX11CreateEffectFromMemory(&compiled_shader.front(), compiled_shader.size(), NULL, direct3d_device, effect);
    if (FAILED(hr))
      throw GameException("D3DX11CreateEffectFromMemory() failed.", hr);
  }

  void Effect::SetEffect(ID3DX11Effect* effect) {
    if (effect_ != nullptr) {
      for (Technique* technique : techniques_)
        delete technique;
      techniques_.clear();

      for (Variable* variable : variables_)
        delete variable;
      variables_.clear();

      effect_ = effect;
      Initialize();
    }
  }

  void Effect::CompileFromFile(const std::wstring& filename) {
    CompileEffectFromFile(game_.Direct3DDevice(), &effect_, filename);
    Initialize();
  }

  void Effect::LoadCompiledEffect(const std::wstring& filename) {
    LoadCompiledEffect(game_.Direct3DDevice(), &effect_, filename);
    Initialize();
  }

  void Effect::Initialize() {
    HRESULT hr = effect_->GetDesc(&effect_desc_);
    if (FAILED(hr))
      throw GameException("ID3DX11Effect::GetDesc() failed.", hr);

    for (UINT i = 0; effect_desc_.Techniques; i++) {
      Technique* technique = new Technique(game_, *this, effect_->GetTechniqueByIndex(i));
      techniques_.push_back(technique);
      techniques_by_name_.insert(std::pair<std::string, Technique*>(technique->Name(), technique));
    }

    for (UINT i = 0; i < effect_desc_.GlobalVariables; i++) {
      Variable* variable = new Variable(*this, effect_->GetConstantBufferByIndex(i));
      variables_.push_back(variable);
      variables_by_name_.insert(std::pair<std::string, Variable*>(variable->Name(), variable));
    }
  }

} // namespace Library