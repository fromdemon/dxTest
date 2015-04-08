#include "rendering_game.hpp"
#include "game_exception.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "fps_component.hpp"
#include "first_person_camera.hpp"
#include "render_state_helper.hpp"
#include "color_helper.hpp"
#include "triangle_demo.hpp"

namespace Rendering {

const XMVECTORF32 RenderingGame::BackgroundColor = ColorHelper::CornflowerBlue;

  RenderingGame::RenderingGame(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand) : Game(instance, windowClass, windowTitle, showCommand) {
    mDepthStencilBufferEnabled = true;
    mMultiSamplingEnabled = true;
  }
  
  RenderingGame::~RenderingGame() {}

  void RenderingGame::Shutdown() {
    DeleteObject(mDemo);
    DeleteObject(mRenderStateHelper);
    DeleteObject(mKeyboard);
    DeleteObject(mMouse);
    DeleteObject(mFpsComponent);
    DeleteObject(mCamera);

    ReleaseObject(mDirectInput);

    Game::Shutdown();
  }

  void RenderingGame::Initialize() {
    if (FAILED(DirectInput8Create(mInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&mDirectInput, nullptr)))
      throw Library::GameException("DirectInput8Create() failed.");

    mKeyboard = new Keyboard(*this, mDirectInput);
    mComponent.push_back(mKeyboard);
    mServices.AddService(Library::Keyboard::TypeIdClass(), mKeyboard);

    mMouse = new Mouse(*this, mDirectInput);
    mComponent.push_back(mMouse);
    mServices.AddService(Mouse::TypeIdClass(), mMouse);

    mCamera = new FirstPersonCamera(*this);
    mComponent.push_back(mCamera);
    mServices.AddService(FirstPersonCamera::TypeIdClass(), mCamera);

    mFpsComponent = new FpsComponent(*this);
    mFpsComponent->Initialize();

    mRenderStateHelper = new RenderStateHelper(*this);

    mDemo = new TriangleDemo(*this, *mCamera);
    mComponent.push_back(mDemo);

    Game::Initialize();
    mCamera->SetPosition(0.0f, 0.0f, 10.0f);
  }

  void RenderingGame::Update(const Library::GameTime& gameTime) {
    mFpsComponent->Update(gameTime);

    if (mKeyboard->WasKeyPressedThisFrame(DIK_ESCAPE))
      Exit();

    Game::Update(gameTime);
  }

  void RenderingGame::Draw(const GameTime &gameTime)
  {
    mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&BackgroundColor));
    mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

    Game::Draw(gameTime);
    Sleep(3);
    mRenderStateHelper->SaveAll();
    mFpsComponent->Draw(gameTime);
    mRenderStateHelper->RestoreAll();

    HRESULT hr = mSwapChain->Present(0, 0);
    if (FAILED(hr))
    {
      throw GameException("IDXGISwapChain::Present() failed.", hr);
    }
  }

} // namespace Rendering