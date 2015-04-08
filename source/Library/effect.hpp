#pragma once

#include "common.hpp"
#include "technique.hpp"
#include "variable.hpp"


namespace Library {

  class Game;

  class Effect {
  public:
    Effect(Game& game);
    Effect(const Effect&) = delete;

    Effect& operator=(const Effect&) = delete;
    virtual ~Effect();

    static void CompileEffectFromFile(ID3D11Device* direct3d_device, ID3DX11Effect** effect, const std::wstring& filename);
    static void LoadCompiledEffect(ID3D11Device* direct3d_device, ID3DX11Effect** effect, const std::wstring& filename);

    Game& GetGame() { return game_; }
    ID3DX11Effect* GetEffect() const { return effect_; }
    void SetEffect(ID3DX11Effect* effect);
    const D3DX11_EFFECT_DESC& EffectDesc() const { return effect_desc_; }
    const std::vector<Technique*>& Techniques() const { return techniques_; }
    const std::map<std::string, Technique*>& TechniquesByName() const { return techniques_by_name_; }
    const std::vector<Variable*>& Variables() const { return variables_; }
    const std::map<std::string, Variable*>& VariablesByName() { return variables_by_name_; }

    void CompileFromFile(const std::wstring& filename);
    void LoadCompiledEffect(const std::wstring& filename);

  private:
    void Initialize();

    Game& game_;
    ID3DX11Effect* effect_ = nullptr;
    D3DX11_EFFECT_DESC effect_desc_;

    std::vector<Technique*> techniques_;
    std::map<std::string, Technique*> techniques_by_name_;
    std::vector<Variable*> variables_;
    std::map<std::string, Variable*> variables_by_name_;
  }; // class Effect

} // namespace Library