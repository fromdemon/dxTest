#include "game_time.hpp"

namespace Library {

  GameTime::GameTime() : mElapsedGameTime(0.0), mTotalGameTime(0.0) {
  }

  double GameTime::ElapsedGameTime() const {
    return mElapsedGameTime;
  }

  void GameTime::SetElapsedGameTime(double elapsedGameTime) {
    mElapsedGameTime = elapsedGameTime;
  }

  double GameTime::TotalGameTime() const {
    return mTotalGameTime;
  }

  void GameTime::SetTotalGameTime(double totalGameTime) {
    mTotalGameTime = totalGameTime;
  }

} // namespace Library