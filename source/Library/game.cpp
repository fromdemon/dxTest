#include "game.hpp"

namespace Library {

  const unsigned int Game::DefaultScreenWidth = 640;
  const unsigned int Game::DefaultScreenHeight = 480;

  Game::Game(HINSTANCE instance, const std::wstring& windowClass, const std::wstring& windowTitle, int showCommand) : mInstance(instance), mWindowClass(windowClass), mWindowTitle(windowTitle), mShowCommand(showCommand),
    mWindow(), mWindowHandle(), mScreenWidth(DefaultScreenWidth), mScreenHeight(DefaultScreenHeight), mGameTime(), mGameClock() {
  }

  Game::~Game() {
  }

  void Game::Initialize() {
  }

  void Game::Run() {
    InitializeWindow();
    Initialize();

    MSG message;
    ZeroMemory(&message, sizeof(message));

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
    mWindow.hCursor = LoadCursor(nullptr, IDC_UPARROW);
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

  void Game::Shutdown() {
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