#pragma once

#include "common.hpp"
#include "game.hpp"

using namespace Library;

namespace Library {
class Keyboard;
class Mouse;
class FirstPersonCamera;
class FpsComponent;
class RenderStateHelper;
}

namespace Rendering {

class TriangleDemo;

class RenderingGame : public Library::Game {
public:
  RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
  ~RenderingGame();

  virtual void Initialize() override;
  virtual void Update(const Library::GameTime& gameTime) override;
  virtual void Draw(const Library::GameTime& gameTime) override;

protected:
  virtual void Shutdown() override;

private:
  static const XMVECTORF32 BackgroundColor;
  LPDIRECTINPUT8 mDirectInput = nullptr;
  Keyboard* mKeyboard = nullptr;
  Mouse* mMouse = nullptr;
  FirstPersonCamera* mCamera = nullptr;
  FpsComponent* mFpsComponent = nullptr;
  RenderStateHelper* mRenderStateHelper = nullptr;

  TriangleDemo* mDemo = nullptr;
}; // class RenderingGame

} // namespace Rendering