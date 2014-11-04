#pragma once

#include "common.hpp"
#include "game_clock.hpp"
#include "game_time.hpp"
#include <SDL.h>

namespace Library {

  class Game {
  public:
    Game(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand);

    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    HINSTANCE instance() const { return mInstance; }
    HWND WindowHandle() const { return mWindowHandle; }
    const WNDCLASSEX& Window() const { return mWindow; }
    unsigned int ScreenWidth() const { return mScreenWidth; }
    unsigned int ScreenHeight() const { return mScreenHeight; }
    const std::wstring& WindowClass() const { return mWindowClass; }
    const std::wstring& WindowTitle() const { return mWindowTitle; }

    ID3D11Device1* Direct3DDevice() const { return mDirect3DDevice; }
    ID3D11DeviceContext1* Direct3DDeviceContext() const { return mDirect3DDeviceContext; }
    bool DepthBufferStencilEnabled() const { return mDepthStencilBufferEnabled; }
    float AspectRatio() const { return (float)(mScreenWidth / mScreenHeight); }
    bool IsfullScreen() const { return mIsFullscreen; }
    const D3D11_TEXTURE2D_DESC& BackBufferDesc() const { return mBackBufferDesc; }
    const D3D11_VIEWPORT& Viewport() const { return mViewport; }

    virtual void Initialize();
    virtual void Run();
    virtual void Exit();
    virtual void Update(const GameTime& gameTime);
    virtual void Draw(const GameTime& gameTime);

  protected:
    virtual void InitializeWindow();
    virtual void InitializeDirectX();
    virtual void Shutdown();

    static const unsigned int DefaultScreenWidth;
    static const unsigned int DefaultScreenHeight;
    static const unsigned int DefaultFrameRate;
    static const unsigned int DefaultMultiSamplingRate;
    unsigned int mScreenWidth;
    unsigned int mScreenHeight;

    HINSTANCE mInstance;
    std::wstring mWindowClass;
    std::wstring mWindowTitle;
    int mShowCommand;

    HWND mWindowHandle;
    WNDCLASSEX mWindow;

    GameTime mGameTime;
    GameClock mGameClock;
    
    D3D_FEATURE_LEVEL mFeatureLevel = D3D_FEATURE_LEVEL_11_1;
    ID3D11Device1* mDirect3DDevice = nullptr;
    ID3D11DeviceContext1* mDirect3DDeviceContext = nullptr;
    IDXGISwapChain1* mSwapChain = nullptr;

    unsigned int mFrameRate;
    bool mIsFullscreen = false;
    bool mDepthStencilBufferEnabled = false;
    bool mMultiSamplingEnabled = false;
    unsigned int mMultiSamplingCount;
    unsigned int mMultiSamplingQualityLevels = 0;

    ID3D11Texture2D* mDepthStencilBuffer = nullptr;
    D3D11_TEXTURE2D_DESC mBackBufferDesc;
    ID3D11RenderTargetView* mRenderTargetView = nullptr;
    ID3D11DepthStencilView* mDepthStencilView = nullptr;
    D3D11_VIEWPORT mViewport;
    SDL_Window* window_;
    int width = 800, height = 600;
    bool running_ = true;
    SDL_Rect rect;
    SDL_Surface* screen_, *window_screen_;

  private:
    POINT CenterWindow(int windowWidth, int windowHeight);
    static LRESULT WINAPI WndProc(HWND windowHandle, unsigned int message, WPARAM wParam, LPARAM lParam);
  }; // class Game

} // namespace Library