#include "technique.hpp"
#include "game.hpp"

namespace Library {

  Technique::Technique(Game& game, Effect& effect, ID3DX11EffectTechnique* technique) : effect_(effect), technique_(technique) {
    technique_->GetDesc(&technique_desc_);
    name_ = technique_desc_.Name;

    for (UINT i = 0; i < technique_desc_.Passes; i++) {
      Pass* pass = new Pass(game, *this, technique->GetPassByIndex(i));
      passes_.push_back(pass);
      passes_by_name_.insert(std::pair<std::string, Pass*>(pass->Name(), pass));
    }
  }

  Technique::~Technique() {
    for (Pass* pass : passes_)
         delete pass;
  }

} // namespace Library
