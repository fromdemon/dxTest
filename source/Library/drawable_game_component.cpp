#include "drawable_game_component.hpp"

namespace Library {

  DrawableGameComponent::DrawableGameComponent(Game& game) : GameComponent(game) {
  }

  DrawableGameComponent::DrawableGameComponent(Game& game, Camera& camera) : GameComponent(game), mCamera(camera) {
  }

  DrawableGameComponent::~DrawableGameComponent() {
  }

  void DrawableGameComponent::Draw(GameTime& gameTime) {
  }

} // namespace Library