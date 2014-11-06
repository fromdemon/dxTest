#include "camera.hpp"
#include "game.hpp"
#include "game_time.hpp"
#include "vector_helper.hpp"
#include "matrix_helper.hpp"

namespace Library {

RTTI_DEFINITIONS(Camera)

const float Camera::DefaultFieldOfView = XM_PIDIV4;
const float Camera::DefaultNearPlanceDistance = 0.01f;
const float Camera::DefaultFarPlaneDistance = 1000.0f;

Camera::Camera(Game& game) : GameComponent(game), mFieldOfView(DefaultFieldOfView), mAspectRatio(game.AspectRatio()), mNearPlaneDistance(DefaultNearPlanceDistance), mFarPlaneDistance(DefaultFarPlaneDistance),
mPosition(), mDirection(), mUp(), mRight(), mViewMatrix(), mProjectionMatrix() {}

Camera::Camera(Game& game, float field_of_view, float aspect_ratio, float near_plance_distance, float far_plane_distance) : GameComponent(game), mFieldOfView(field_of_view), 
                                                                                                                            mAspectRatio(aspect_ratio), mNearPlaneDistance(near_plance_distance),
                                                                                                                            mFarPlaneDistance(far_plane_distance), mPosition(), mDirection(), mUp(), 
                                                                                                                            mRight(), mViewMatrix(), mProjectionMatrix() {}

Camera::~Camera() {}

XMMATRIX Camera::ViewProjectionMatrix() const {
  XMMATRIX viewMatrix = XMLoadFloat4x4(&mViewMatrix);
  XMMATRIX projectionMatrix = XMLoadFloat4x4(&mProjectionMatrix);

  return XMMatrixMultiply(viewMatrix, projectionMatrix);
}

void Camera::SetPosition(float x, float y, float z) {
  XMVECTOR position = XMVectorSet(x, y, z, 1.0f);
  SetPosition(position);
}

void Camera::SetPosition(FXMVECTOR position) {
  XMStoreFloat3(&mPosition, position);
}

void Camera::SetPosition(const XMFLOAT3& transform) {
  mPosition = transform;
}

void Camera::Reset() {
  mPosition = Vector3Helper::Zero;
  mDirection = Vector3Helper::Forward;
  mUp = Vector3Helper::Up;
  mRight = Vector3Helper::Right;

  UpdateViewMatrix();
}

void Camera::Initialize() {
  UpdateProjectionMatrix();
  Reset();
}

void Camera::Update(const GameTime& game_time) {
  UpdateViewMatrix();
}

void Camera::UpdateViewMatrix() {
  XMVECTOR eyePosition = XMLoadFloat3(&mPosition);
  XMVECTOR direction = XMLoadFloat3(&mDirection);
  XMVECTOR upDirection = XMLoadFloat3(&mUp);

  XMMATRIX viewMatrix = XMMatrixLookToRH(eyePosition, direction, upDirection);
  XMStoreFloat4x4(&mViewMatrix, viewMatrix);
}

void Camera::UpdateProjectionMatrix() {
  XMMATRIX projectionMatrix = XMMatrixPerspectiveFovRH(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
  XMStoreFloat4x4(&mProjectionMatrix, projectionMatrix);
}

void Camera::ApplyRotation(CXMMATRIX transform) {
  XMVECTOR direction = XMLoadFloat3(&mDirection);
  XMVECTOR up = XMLoadFloat3(&mUp);

  direction = XMVector3TransformNormal(direction, transform);
  direction = XMVector3Normalize(direction);

  up = XMVector3TransformNormal(up, transform);
  up = XMVector3Normalize(up);

  XMVECTOR right = XMVector3Cross(direction, up);
  up = XMVector3Cross(right, direction);

  XMStoreFloat3(&mDirection, direction);
  XMStoreFloat3(&mUp, up);
  XMStoreFloat3(&mRight, right);
}

void Camera::ApplyRotation(const XMFLOAT4X4& transform) {
  XMMATRIX transformMatrix = XMLoadFloat4x4(&transform);
  ApplyRotation(transformMatrix);
}

} // namespace Library