#include <memory>
#include "rendering_game.hpp"
#include "game_exception.hpp"

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showCommand) {
#if defined(DEBUG) || defined(_DEBUG)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

  std::unique_ptr<Rendering::RenderingGame> game(new Rendering::RenderingGame(instance, L"RenderingClass", L"Real-time rendering.", showCommand));

  try {
    game->Run();
  }
  catch (Library::GameException e) {
    MessageBox(game->WindowHandle(), e.Whatw().c_str(), game->WindowTitle().c_str(), MB_ABORTRETRYIGNORE);
  }

  return 0;
}