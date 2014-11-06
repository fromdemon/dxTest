#include "drawable_game_component.hpp"

namespace Library {

  RTTI_DEFINITIONS(DrawableGameComponent)

  DrawableGameComponent::DrawableGameComponent(Game& game) : GameComponent(game) {
  }

  DrawableGameComponent::DrawableGameComponent(Game& game, Camera& camera) : GameComponent(game), mCamera(&camera) {
  }

  DrawableGameComponent::~DrawableGameComponent() {
  }

  void DrawableGameComponent::Draw(const GameTime& gameTime) {
  }
  
} // namespace Library