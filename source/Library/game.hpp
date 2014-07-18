#pragma once

#include <windows.h>
#include <string>
#include "game_clock.hpp"
#include "game_time.hpp"

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

    virtual void Initialize();
    virtual void Run();
    virtual void Exit();
    virtual void Update(const GameTime& gameTime);
    virtual void Draw(const GameTime& gameTime);

  protected:
    virtual void InitializeWindow();
    virtual void Shutdown();

    static const unsigned int DefaultScreenWidth;
    static const unsigned int DefaultScreenHeight;
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

    POINT CenterWindow(int windowWidth, int windowHeight);
    static LRESULT WINAPI WndProc(HWND windowHandle, unsigned int message, WPARAM wParam, LPARAM lParam);
  }; // class Game

} // namespace Library