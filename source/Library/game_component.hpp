#pragma once

#include "common.hpp"

namespace Library {

  class Game;
  class GameTime;

  class GameComponent : public RTTI {
    RTTI_DECLARATION(GameComponent, RTTI)

  public:
    GameComponent() = default;
    GameComponent(Game& game);
    virtual ~GameComponent();

    GameComponent(const GameComponent&) = delete;
    GameComponent& operator=(const GameComponent&) = delete;

    Game* GetGame();
    void SetGame(Game& game);
    bool Enabled() const;
    void SetEnabled(bool enabled);

    virtual void Initialize();
    virtual void Update(const GameTime& gameTime);

  protected:
    Game* mGame = nullptr;
    bool mEnabled = true;
  }; // class GameComponent

} // namespace Library