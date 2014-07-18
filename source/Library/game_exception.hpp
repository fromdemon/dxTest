#pragma once

#include <string>
#include <windows.h>
#include <exception>

namespace Library {

  class GameException : std::exception {
  public:
    GameException(const char* message, HRESULT hr = S_OK);
    
    HRESULT Hr() const;
    std::wstring Whatw() const;

  private:
    HRESULT mHr;
  }; // class GameException

} // namespace Library