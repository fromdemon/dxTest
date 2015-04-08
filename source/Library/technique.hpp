#pragma once

#include "common.hpp"
#include "pass.hpp"

namespace Library {

  class Game;
  class Effect;

  class Technique {
  public:
    Technique(Game& game, Effect& effect, ID3DX11EffectTechnique* technique);
    Technique(const Technique&) = delete;

    Technique& operator=(const Technique&) = delete;
    ~Technique();

    Effect& GetEffect() { return effect_; }
    ID3DX11EffectTechnique* GetTechnique() const { return technique_; }
    const D3DX11_TECHNIQUE_DESC& TechniqueDesc() const { return technique_desc_; }
    const std::string& Name() const { return name_; }
    const std::vector<Pass*>& Passes() const { return passes_; }
    const std::map<std::string, Pass*>& PassesByName() const { return passes_by_name_; }

  private:
    Effect& effect_;
    ID3DX11EffectTechnique* technique_;
    D3DX11_TECHNIQUE_DESC technique_desc_;
    std::string name_;
    std::vector<Pass*> passes_;
    std::map<std::string, Pass*> passes_by_name_;
  }; // class Technique

} // namespace Library