#include "fps_component.hpp"
#include "utility.hpp"
#include "game.hpp"

#include <iomanip>
#include <sstream>
#include <SpriteBatch.h>
#include <SpriteFont.h>

namespace Library {

  RTTI_DEFINITIONS(FpsComponent)

  FpsComponent::FpsComponent(Game& game) : DrawableGameComponent(game) {
  }

  FpsComponent::~FpsComponent() {
    DeleteObject(mSpriteBatch);
    DeleteObject(mSpriteFont);
  }

  void FpsComponent::Initialize() {
    SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

    mSpriteBatch = new SpriteBatch(mGame->Direct3DDeviceContext());
    mSpriteFont = new SpriteFont(mGame->Direct3DDevice(), L"Content\\Fonts\\Arial_14_Regular.spritefont");
  }

  void FpsComponent::Update(const GameTime& gameTime) {
    if (gameTime.TotalGameTime() - mLastTotalElapsedTime >= 1) {
      mLastTotalElapsedTime = gameTime.TotalGameTime();
      mFrameRate = mFrameCount;
      mFrameCount = 0;
    }

    mFrameCount++;
  }

  void FpsComponent::Draw(const GameTime& gameTime) {
    mSpriteBatch->Begin();
    
    std::wostringstream fpsLabel;
    fpsLabel << std::setprecision(4) << L"Frame rate: " << mFrameRate << L"    Total elapsed time: " << gameTime.TotalGameTime();
    mSpriteFont->DrawString(mSpriteBatch, fpsLabel.str().c_str(), mTextPosition);

    mSpriteBatch->End();
  }
} // namespace Library