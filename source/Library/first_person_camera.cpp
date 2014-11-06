#include "first_person_camera.hpp"
#include "game.hpp"
#include "game_time.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "vector_helper.hpp"

namespace Library {

RTTI_DEFINITIONS(FirstPersonCamera)

const float FirstPersonCamera::DefaultMouseSensitivity = 100.0f;
const float FirstPersonCamera::DefaultRotationRate = XMConvertToRadians(1.0f);
const float FirstPersonCamera::DefaultMovementRate = 10.0f;

FirstPersonCamera::FirstPersonCamera(Game& game) : Camera(game), mMouseSensitivity(DefaultMouseSensitivity), mRotationRate(DefaultRotationRate), mMovementRate(DefaultMovementRate) {}

FirstPersonCamera::FirstPersonCamera(Game& game, float field_of_view, float aspect_ratio, float near_plane_distance, float far_plane_distance) : Camera(game, field_of_view, aspect_ratio, near_plane_distance, far_plane_distance), mMouseSensitivity(DefaultMouseSensitivity), mRotationRate(DefaultRotationRate), mMovementRate(DefaultMovementRate) {}

FirstPersonCamera::~FirstPersonCamera() {
  mMouse = nullptr;
  mKeyboard = nullptr;
}

void FirstPersonCamera::Initialize() {
  mKeyboard = (Keyboard*)mGame->Services().GetService(Keyboard::TypeIdClass());
  mMouse = (Mouse*)mGame->Services().GetService(Mouse::TypeIdClass());

  Camera::Initialize();
}

void FirstPersonCamera::Update(const GameTime& gameTime) {
  XMFLOAT2 movementAmount = Vector2Helper::Zero;
  if (mKeyboard != nullptr)
  {
    if (mKeyboard->IsKeyDown(DIK_W))
    {
      movementAmount.y = 1.0f;
    }

    if (mKeyboard->IsKeyDown(DIK_S))
    {
      movementAmount.y = -1.0f;
    }

    if (mKeyboard->IsKeyDown(DIK_A))
    {
      movementAmount.x = -1.0f;
    }

    if (mKeyboard->IsKeyDown(DIK_D))
    {
      movementAmount.x = 1.0f;
    }
  }

  XMFLOAT2 rotationAmount = Vector2Helper::Zero;
  if ((mMouse != nullptr) && (mMouse->IsButtonHeldDown(MouseButtonLeft)))
  {
    LPDIMOUSESTATE mouseState = mMouse->CurrentState();
    rotationAmount.x = -mouseState->lX * mMouseSensitivity;
    rotationAmount.y = -mouseState->lY * mMouseSensitivity;
  }

  float elapsedTime = (float)gameTime.ElapsedGameTime();
  XMVECTOR rotationVector = XMLoadFloat2(&rotationAmount) * mRotationRate * elapsedTime;
  XMVECTOR right = XMLoadFloat3(&mRight);

  XMMATRIX pitchMatrix = XMMatrixRotationAxis(right, XMVectorGetY(rotationVector));
  XMMATRIX yawMatrix = XMMatrixRotationY(XMVectorGetX(rotationVector));

  ApplyRotation(XMMatrixMultiply(pitchMatrix, yawMatrix));

  XMVECTOR position = XMLoadFloat3(&mPosition);
  XMVECTOR movement = XMLoadFloat2(&movementAmount) * mMovementRate * elapsedTime;

  XMVECTOR strafe = right * XMVectorGetX(movement);
  position += strafe;

  XMVECTOR forward = XMLoadFloat3(&mDirection) * XMVectorGetY(movement);
  position += forward;

  XMStoreFloat3(&mPosition, position);

  Camera::Update(gameTime);
}

} // namespace Library