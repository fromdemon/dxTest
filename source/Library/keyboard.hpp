#pragma once

#include "game_component.hpp"

namespace Library {

class Keyboard : public GameComponent {
  RTTI_DECLARATIONS(Keyboard, GameComponent)
public:
  Keyboard() = default;
  Keyboard(const Keyboard&) = delete;
  Keyboard(Game& game, LPDIRECTINPUT8 directInput);
  ~Keyboard();

  const byte* const CurrentState() const { return mCurrentState; }
  const byte* const PreviousState() const { return mPreviousState; }

  virtual void Initialize() override;
  virtual void Update(const GameTime& gameTime) override;

  bool IsKeyDown(byte key) const { return ((mCurrentState[key] & 0x80) != 0); }
  bool IsKeyUp(byte key) const { return ((mCurrentState[key] & 0x80) == 0); }
  bool WasKeyDown(byte key) const { return ((mPreviousState[key] & 0x80) != 0); }
  bool WasKeyUp(byte key) const { return ((mPreviousState[key] & 0x80) == 0); }
  bool WasKeyReleaseThisFrame(byte key) const { return IsKeyUp(key) && WasKeyDown(key); }
  bool WasKeyPressedThisFrame(byte key) const { return IsKeyDown(key) && WasKeyUp(key); }
  bool IsKeyHeldDown(byte key) const { return IsKeyDown(key) && WasKeyDown(key); }

private:
  static const int KeyCount = 256;
  LPDIRECTINPUT8 mDirectInput = nullptr;
  LPDIRECTINPUTDEVICE8 mDevice;
  byte mCurrentState[KeyCount];
  byte mPreviousState[KeyCount];
};

} // namespace Library