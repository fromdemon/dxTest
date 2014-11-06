#pragma once

#include "camera.hpp"

namespace Library {

class Mouse;
class Keyboard;

class FirstPersonCamera : public Camera {
  RTTI_DECLARATIONS(FirstPersonCamera, Camera)
public:
  FirstPersonCamera() = delete;
  FirstPersonCamera(const FirstPersonCamera&) = delete;
  FirstPersonCamera(Game& game);
  FirstPersonCamera(Game& game, float field_of_view, float aspect_ratio, float near_plane_distance, float far_plane_distance);
  virtual ~FirstPersonCamera();

  FirstPersonCamera& operator=(const FirstPersonCamera&) = delete;

  const Keyboard& GetKeyboard() const { return *mKeyboard; }
  const Mouse& GetMouse() const { return *mMouse; }
  void SetKeyboard(Keyboard& keyboard) { mKeyboard = &keyboard; }
  void SetMouse(Mouse& mouse) { mMouse = &mouse; }

  float& MouseSensitivity() { return mMouseSensitivity; }
  float& RotationRate() { return mRotationRate; }
  float& MovementRate() { return mMovementRate; }

  void Initialize() override;
  void Update(const GameTime& game_time) override;

  static const float DefaultMouseSensitivity;
  static const float DefaultRotationRate;
  static const float DefaultMovementRate;

protected:
  float mMouseSensitivity;
  float mRotationRate;
  float mMovementRate;

  Keyboard* mKeyboard = nullptr;
  Mouse* mMouse = nullptr;
};

} // namespace Library