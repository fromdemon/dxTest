#pragma once

#include <windows.h>

namespace Library {

  class GameTime;

  class GameClock {
  public:
    GameClock();

    const LARGE_INTEGER& StartTime() const;
    const LARGE_INTEGER& CurrentTime() const;
    const LARGE_INTEGER& LastTime() const;

    void Reset();
    double Frequency() const;
    void GetTime(LARGE_INTEGER& time) const;
    void UpdateGameTime(GameTime& gameTime);

    GameClock(const GameClock&) = delete;
    GameClock& operator=(const GameClock&) = delete;

  private:
    LARGE_INTEGER mStartTime;
    LARGE_INTEGER mCurrentTime;
    LARGE_INTEGER mLastTime;
    double mFrequency;

  }; // class GameClock

} // namespace Library