#pragma once

#include "common.hpp"
#include "game.hpp"

namespace Rendering {

  class RenderingGame : public Library::Game {
  public:
    RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);
    ~RenderingGame();

    virtual void Initialize() override;
    virtual void Update(const Library::GameTime& gameTime) override;
    virtual void Draw(const Library::GameTime& gameTime) override;
  
  private:
    static const XMVECTORF32 BackgroundColor;
  }; // class RenderingGame

} // namespace Rendering