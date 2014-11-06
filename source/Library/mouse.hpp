#pragma once

#include "game_component.hpp"

namespace Library {

class GameTime;

enum MouseButtons {
  MouseButtonLeft = 0,
  MouseButtonRight = 1,
  MouseButtonMiddle = 2,
  MousebuttonX1 = 3
};

class Mouse : public GameComponent {
  RTTI_DECLARATIONS(Mouse, GameComponent)
public:
  Mouse() = delete;
  Mouse(Game& game, LPDIRECTINPUT8 directInput);
  ~Mouse();

  LPDIMOUSESTATE CurrentState() { return &mCurrentState; }
  LPDIMOUSESTATE PreviousState() { return &mPreviousState; }

  virtual void Initialize() override;
  virtual void Update(const GameTime& gameTime) override;

  long X() const { return mX; }
  long Y() const { return mY; }
  long Wheel() const { return mWheel; }

  bool IsButtonUp(MouseButtons button) const { return ((mCurrentState.rgbButtons[button] & 0x80) == 0); }
  bool IsButtonDown(MouseButtons button) const { return ((mCurrentState.rgbButtons[button] & 0x80) != 0); }
  bool WasButtonUp(MouseButtons button) const { return ((mPreviousState.rgbButtons[button] & 0x80) == 0); }
  bool WasButtonDown(MouseButtons button) const { return ((mPreviousState.rgbButtons[button] & 0x80) != 0); }
  bool WasButtonPressedThisFrame(MouseButtons button) const { return IsButtonDown(button) && WasButtonUp(button); }
  bool WasButtonReleaseThisFrame(MouseButtons button) const { return IsButtonUp(button) && WasButtonDown(button); }
  bool IsButtonHeldDown(MouseButtons button) const { return IsButtonDown(button) && WasButtonDown(button); }

private:
  LPDIRECTINPUT8 mDirectInput;
  LPDIRECTINPUTDEVICE8 mDevice = nullptr;
  DIMOUSESTATE mCurrentState;
  DIMOUSESTATE mPreviousState;

  long mX = 0;
  long mY = 0;
  long mWheel = 0;
};

} // namespace Library