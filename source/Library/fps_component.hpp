#pragma once

#include "drawable_game_component.hpp"

namespace DirectX {

  class SpriteBatch;
  class SpriteFont;

} // namespace DirectX

namespace Library {

  class FpsComponent : public DrawableGameComponent {
    RTTI_DECLARATION(FpsComponent, DrawableGameComponent)

  public:
    FpsComponent() = delete;
    FpsComponent(Game& game);
    FpsComponent(const FpsComponent&) = delete;
    FpsComponent& operator=(const FpsComponent&) = delete;
    ~FpsComponent();

    XMFLOAT2& TextPosition() { return mTextPosition; }
    int FrameRate() { return mFrameRate; }

    virtual void Initialize() override;
    virtual void Update(const GameTime& gameTime) override;
    virtual void Draw(const GameTime& gameTime) override;

  private:
    SpriteBatch* mSpriteBatch = nullptr;
    SpriteFont* mSpriteFont = nullptr;
    XMFLOAT2 mTextPosition = {0.0f, 60.0f};

    int mFrameCount = 0;
    int mFrameRate = 0;
    double mLastTotalElapsedTime = 0.0;
  }; // class FpsComponent

} // namespace Library