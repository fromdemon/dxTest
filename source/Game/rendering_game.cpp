#include "rendering_game.hpp"
#include "game_exception.hpp"

namespace Rendering {

  const XMVECTORF32 RenderingGame::BackgroundColor = { 0.0f, 0.0f, 0.0f, 1.0f };

  RenderingGame::RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand) : Game(instance, windowClass, windowTitle, showCommand) {
    mDepthStencilBufferEnabled = true;
    mMultiSamplingEnabled = true;
  }
  
  RenderingGame::~RenderingGame() {
  }

  void RenderingGame::Initialize() {
    Game::Initialize();
  }

  void RenderingGame::Update(const Library::GameTime& gameTime) {
    Game::Update(gameTime);
  }

  void RenderingGame::Draw(const Library::GameTime& gameTime) {
    mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&BackgroundColor));
    mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    Sleep(100);

    Game::Draw(gameTime);
    HRESULT hr = mSwapChain->Present(0, 0);
    if (FAILED(hr))
      throw Library::GameException("IDXGISwapChain::Present() failed.", hr);
  }

} // namespace Rendering