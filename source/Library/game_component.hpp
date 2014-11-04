#pragma once

#include "common.hpp"

namespace Library {

class Game;
class GameTime;

class GameComponent : public RTTI {
  RTTI_DECLARATIONS(GameComponent, RTTI)
    GameComponent()
};


} // namespace Library