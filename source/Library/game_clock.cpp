#include "game_clock.hpp"
#include "game_time.hpp"
#include "game_exception.hpp"

namespace Library {

  GameClock::GameClock() {
    mFrequency = Frequency();
    Reset();
  }

  void GameClock::Reset() {
    GetTime(mStartTime);
    mLastTime = mCurrentTime = mStartTime;
  }

  const LARGE_INTEGER& GameClock::StartTime() const {
    return mStartTime;
  }

  const LARGE_INTEGER& GameClock::CurrentTime() const {
    return mCurrentTime;
  }

  const LARGE_INTEGER& GameClock::LastTime() const {
    return mLastTime;
  }

  void GameClock::GetTime(LARGE_INTEGER& time) const {
    QueryPerformanceCounter(&time);
  }

  double GameClock::Frequency() const {
    LARGE_INTEGER freq;
    if (QueryPerformanceFrequency(&freq) == false)
      throw new GameException("QueryPerformanceFrequency() failed.");

    return (double)freq.QuadPart;
  }

  void GameClock::UpdateGameTime(GameTime& gameTime) {
    GetTime(mCurrentTime);
    
    gameTime.SetElapsedGameTime((mCurrentTime.QuadPart - mLastTime.QuadPart) / mFrequency);
    gameTime.SetTotalGameTime((mCurrentTime.QuadPart - mStartTime.QuadPart) / mFrequency);

    mLastTime = mCurrentTime;
  }

} // namespace Library