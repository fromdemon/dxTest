#include "mouse.hpp"
#include "game.hpp"
#include "game_time.hpp"
#include "game_exception.hpp"

namespace Library {

RTTI_DEFINITIONS(Mouse)

Mouse::Mouse(Game& game, LPDIRECTINPUT8 directInput) : GameComponent(game), mDirectInput(directInput) {
  assert(mDirectInput != nullptr);
  ZeroMemory(&mCurrentState, sizeof(mCurrentState));
  ZeroMemory(&mPreviousState, sizeof(mPreviousState));
}

Mouse::~Mouse() {
  if (mDevice != nullptr) {
    mDevice->Unacquire();
    mDevice->Release();
    mDevice = nullptr;
  }
}

void Mouse::Initialize() {
  if (FAILED(mDirectInput->CreateDevice(GUID_SysMouse, &mDevice, nullptr)))
      throw GameException("LPDIRECTINPUT8::CreateDevice() failed.");
  if (FAILED(mDevice->SetDataFormat(&c_dfDIMouse)))
    throw GameException("IDIRECTINPUTDEVICE8::SetDataFormat() failed.");
  if (FAILED(mDevice->SetCooperativeLevel(mGame->WindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
      throw GameException("IDIRECTINPUTDEVICE8::SetCooperative() failed.");
  if (FAILED(mDevice->Acquire()))
    throw GameException("IDIRECTINPUTDEVICE8::Acquire() failed.");
}

void Mouse::Update(const GameTime& gameTime) {
  if (mDevice != nullptr) {
    memcpy(&mPreviousState, &mCurrentState, sizeof(mCurrentState));
    if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), &mCurrentState))) {
      if (SUCCEEDED(mDevice->Acquire())){
        if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), &mCurrentState)))
            return;
      }
    }
  }

  mX += mCurrentState.lX;
  mY += mCurrentState.lY;
  mWheel += mCurrentState.lZ;
}

} // namespace library