#include "game.hpp"
#include "game_exception.hpp"

namespace Library {

  const unsigned int Game::DefaultScreenWidth = 640;
  const unsigned int Game::DefaultScreenHeight = 480;
  const unsigned int Game::DefaultFrameRate = 60;
  const unsigned int Game::DefaultMultiSamplingRate = 4;

  Game::Game(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand) : mInstance(instance), mWindowClass(windowClass), mWindowTitle(windowTitle), mShowCommand(showCommand),
    mWindow(), mWindowHandle(), mScreenWidth(DefaultScreenWidth), mScreenHeight(DefaultScreenHeight), mGameTime(), mGameClock(),
    mMultiSamplingCount(DefaultMultiSamplingRate), mFrameRate(DefaultFrameRate), mViewport() {
  }

  Game::~Game() {
  }

  void Game::Initialize() {
  }

  void Game::Run() {
    InitializeWindow();
    InitializeDirectX();
    Initialize();

    MSG message;
    ZeroMemory(&message, sizeof(message));

    mGameClock.Reset();

    while (message.message != WM_QUIT) {
      if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }
      else {
        mGameClock.UpdateGameTime(mGameTime);
        Update(mGameTime);
        Draw(mGameTime);
      }
    }

    Shutdown();
  }

  void Game::Exit() {
    PostQuitMessage(0);
  }

  void Game::Update(const GameTime& gameTime) {
  }

  void Game::Draw(const GameTime& gameTime) {
  }

  void Game::InitializeWindow() {
    ZeroMemory(&mWindow, sizeof(mWindow));
    mWindow.cbSize = sizeof(WNDCLASSEX);
    mWindow.style = CS_CLASSDC;
    mWindow.lpfnWndProc = WndProc;
    mWindow.hInstance = mInstance;
    mWindow.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    mWindow.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
    mWindow.hCursor = LoadCursor(nullptr, IDC_ARROW);
    mWindow.hbrBackground = GetSysColorBrush(COLOR_3DDKSHADOW);
    mWindow.lpszClassName = mWindowClass.c_str();

    RECT windowRect = {0, 0, mScreenWidth, mScreenHeight};
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    RegisterClassEx(&mWindow);
    POINT center = CenterWindow(mScreenWidth, mScreenHeight);
    mWindowHandle = CreateWindow(mWindowClass.c_str(), mWindowTitle.c_str(), WS_OVERLAPPEDWINDOW, center.x, center.y, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, nullptr, nullptr, mInstance, nullptr);
    ShowWindow(mWindowHandle, mShowCommand);
    UpdateWindow(mWindowHandle);
  }

  void Game::InitializeDirectX() {
    HRESULT hr;
    unsigned int createDeviceFlags = 0;

#if defined(DEBUG) || defined (_DEBUG)
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevels[] = {
      D3D_FEATURE_LEVEL_10_0,
      D3D_FEATURE_LEVEL_10_1,
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_11_1
    };

    ID3D11Device* direct3DDevice;
    ID3D11DeviceContext* direct3DDeviceContext;
    
    if (FAILED(hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &direct3DDevice, &mFeatureLevel, &direct3DDeviceContext)))
      throw GameException("D3D11CreateDevice() failed.", hr);
    
    if (FAILED(hr = direct3DDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(&mDirect3DDevice))))
      throw GameException("ID3D11Device::QueryInterface() failed.", hr);

    if (FAILED(hr = direct3DDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(&mDirect3DDeviceContext))))
      throw GameException("ID3D11DeviceConetext::QueryInterface() failed.", hr);

    ReleaseObject(direct3DDevice);
    ReleaseObject(direct3DDeviceContext);

    mDirect3DDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, mMultiSamplingCount, &mMultiSamplingQualityLevels);
    if (mMultiSamplingCount == 0)
      throw GameException("ID3D11Direct3DDevice::CheckMultiSamplingQualityLevels() failed.");

    DXGI_SWAP_CHAIN_DESC1 swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.Width = mScreenWidth;
    swapChainDesc.Height = mScreenHeight;
    swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    if (mMultiSamplingEnabled) {
      swapChainDesc.SampleDesc.Count = mMultiSamplingCount;
      swapChainDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
    }
    else {
      swapChainDesc.SampleDesc.Count = 1;
      swapChainDesc.SampleDesc.Quality = 0;
    }

    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    IDXGIDevice* dxgiDevice = nullptr;
    if (FAILED(hr = mDirect3DDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgiDevice))))
      throw GameException("ID3D11Direct3DDevice::QueryInterface() failed.", hr);

    IDXGIAdapter* dxgiAdapter = nullptr;
    if (FAILED(hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&dxgiAdapter)))) {
      ReleaseObject(dxgiDevice);
      throw GameException("IDXGIAdapter::GetParent() failed.", hr);
    }

    IDXGIFactory2* dxgiFactory = nullptr;
    if (FAILED(hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(&dxgiFactory)))) {
      ReleaseObject(dxgiDevice);
      ReleaseObject(dxgiAdapter);
      throw GameException("IDXGIFactory2::GetParent() failed.", hr);
    }

    DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc;
    ZeroMemory(&fullscreenDesc, sizeof(fullscreenDesc));
    fullscreenDesc.RefreshRate.Numerator = mFrameRate;
    fullscreenDesc.RefreshRate.Denominator = 1;
    fullscreenDesc.Windowed = !mIsFullscreen;

    if (FAILED(hr = dxgiFactory->CreateSwapChainForHwnd(dxgiDevice, mWindowHandle, &swapChainDesc, &fullscreenDesc, nullptr, &mSwapChain))) {
      ReleaseObject(dxgiDevice);
      ReleaseObject(dxgiAdapter);
      ReleaseObject(dxgiFactory);
      throw GameException("IDXGIFactory2::CreateSwapChainForHwnd() failed.", hr);
    }

    ReleaseObject(dxgiDevice);
    ReleaseObject(dxgiAdapter);
    ReleaseObject(dxgiFactory);

    ID3D11Texture2D* backBuffer;
    if (FAILED(hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer))))
      throw GameException("IDXGISwapChain1::GetBuffer() failed.", hr);

    backBuffer->GetDesc(&mBackBufferDesc);

    if (FAILED(hr = mDirect3DDevice->CreateRenderTargetView(backBuffer, nullptr, &mRenderTargetView))) {
      ReleaseObject(backBuffer);
      throw GameException("ID3D11Direct3DDevice::CreateRenderTargetView() failed.", hr);
    }

    ReleaseObject(backBuffer);

    if (mDepthStencilBufferEnabled) {
      D3D11_TEXTURE2D_DESC depthStencilDesc;
      ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
      depthStencilDesc.Width = mScreenWidth;
      depthStencilDesc.Height = mScreenHeight;
      depthStencilDesc.MipLevels = 1;
      depthStencilDesc.ArraySize = 1;
      depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
      depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
      depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;

      if (mMultiSamplingEnabled) {
        depthStencilDesc.SampleDesc.Count = mMultiSamplingCount;
        depthStencilDesc.SampleDesc.Quality = mMultiSamplingQualityLevels - 1;
      }
      else {
        depthStencilDesc.SampleDesc.Count = 1;
        depthStencilDesc.SampleDesc.Quality = 0;
      }

      if (FAILED(hr = mDirect3DDevice->CreateTexture2D(&depthStencilDesc, nullptr, &mDepthStencilBuffer)))
        throw GameException("ID3D11Direct3DDevice::CreateTexture2D() failed.", hr);

      if (FAILED(hr = mDirect3DDevice->CreateDepthStencilView(mDepthStencilBuffer, nullptr, &mDepthStencilView)))
        throw GameException("ID3D11Direct3DDevice::CreateDepthStencilView() faile.", hr);
    }

    mDirect3DDeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

    mViewport.TopLeftX = 0.0f;
    mViewport.TopLeftY = 0.0f;
    mViewport.Width = static_cast<float>(mScreenWidth);
    mViewport.Height = static_cast<float>(mScreenHeight);
    mViewport.MinDepth = 0.0f;
    mViewport.MaxDepth = 1.0f;

    mDirect3DDeviceContext->RSSetViewports(1, &mViewport);
  }

  void Game::Shutdown() {
    ReleaseObject(mDepthStencilBuffer);
    ReleaseObject(mRenderTargetView);
    ReleaseObject(mDepthStencilView);
    if (mDirect3DDeviceContext != nullptr)
      mDirect3DDeviceContext->ClearState();
    ReleaseObject(mDirect3DDeviceContext);
    ReleaseObject(mDirect3DDevice);

    UnregisterClass(mWindowClass.c_str(), mWindow.hInstance);
  }

  LRESULT WINAPI Game::WndProc(HWND windowHandle, unsigned int message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
    }

    return DefWindowProc(windowHandle, message, wParam, lParam);
  }

  POINT Game::CenterWindow(int windowWidth, int windowHeight) {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    POINT center;
    center.x = (screenWidth - windowWidth) / 2;
    center.y = (screenHeight - windowHeight) / 2;

    return center;
  }

} // namespace Library