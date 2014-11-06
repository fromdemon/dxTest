#pragma once

#include "game_component.hpp"

namespace Library {

  class Camera;

  class DrawableGameComponent : public GameComponent {
    RTTI_DECLARATIONS(DrawableGameComponent, GameComponent)

  public:
    DrawableGameComponent() = default;
    DrawableGameComponent(Game& game);
    DrawableGameComponent(Game& game, Camera& camera);
    DrawableGameComponent(const DrawableGameComponent&) = delete;
    DrawableGameComponent& operator=(const DrawableGameComponent&) = delete;
    virtual ~DrawableGameComponent();

    bool Visible() const { return mVisible; }
    void SetVisible(bool visible) { mVisible = visible; }

    Camera* GetCamera() { return mCamera; }
    void SetCamera(Camera* camera) { mCamera = camera; }

    virtual void Draw(const GameTime& gameTime);

  protected:
    bool mVisible = true;
    Camera* mCamera = nullptr;

  }; // class DrawableGameComponent

} // namespace Library