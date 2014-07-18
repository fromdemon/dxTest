#include "game_exception.hpp"

namespace Library {

  GameException::GameException(const char* message, HRESULT hr) : exception(message), mHr(hr) {
  }

  HRESULT GameException::Hr() const {
    return mHr;
  }

  std::wstring GameException::Whatw() const {
    std::string string(exception::what());
    std::wstring wString;

    wString.assign(string.begin(), string.end());

    return wString;
  }
} // namespace Library