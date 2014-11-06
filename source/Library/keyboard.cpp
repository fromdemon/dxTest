#include "keyboard.hpp"
#include "game.hpp"
#include "game_time.hpp"
#include "game_exception.hpp"

namespace Library {

RTTI_DEFINITIONS(Keyboard)

Keyboard::Keyboard(Game& game, LPDIRECTINPUT8 directInput) : GameComponent(game), mDirectInput(directInput) {
  assert(mDirectInput != nullptr);
  ZeroMemory(mCurrentState, sizeof(mCurrentState));
  ZeroMemory(mPreviousState, sizeof(mPreviousState));
}

Keyboard::~Keyboard() {
  if (mDevice != nullptr) {
    mDevice->Unacquire();
    mDevice->Release();
    mDevice = nullptr;
  }
}

void Keyboard::Initialize() {
  if (FAILED(mDirectInput->CreateDevice(GUID_SysKeyboard, &mDevice, nullptr)))
    throw GameException("IDIRECTINPUT8::CreateDevice() failed.");
  if (FAILED(mDevice->SetDataFormat(&c_dfDIKeyboard)))
    throw GameException("IDIRECTINPUTDEVICE::SetDataFormat() failed.");
  if (FAILED(mDevice->SetCooperativeLevel(mGame->WindowHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
    throw GameException("IDIRECTINPUTDEVICE::SetCooperativeLevel() failed.");
  if (FAILED(mDevice->Acquire()))
    throw GameException("IDIRECTINPUTDEVICE::Avquire() failed.");
}

void Keyboard::Update(const GameTime& gameTime) {
  if (mDevice != nullptr) {
    memcpy(mPreviousState, mCurrentState, sizeof(mCurrentState));

    if (FAILED(mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState))) {
      if (SUCCEEDED(mDevice->Acquire()))
        mDevice->GetDeviceState(sizeof(mCurrentState), (LPVOID)mCurrentState);
    }
  }
}

} // namespace Library