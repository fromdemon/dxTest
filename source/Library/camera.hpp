#pragma once

#include "game_component.hpp"

namespace Library {

class GameTime;

class Camera : public GameComponent {
  RTTI_DECLARATIONS(Camera, GameComponent)
public:
  Camera() = delete;
  Camera(const Camera&) = delete;
  Camera(Game& game);
  Camera(Game& game, float field_of_view, float aspect_ratio, float near_plane_distance, float far_plane_distance);
  virtual ~Camera();

  Camera& operator=(const Camera&) = delete;

  const XMFLOAT3& Position() const { return mPosition; }
  const XMFLOAT3& Direction() const { return mDirection; }
  const XMFLOAT3& Up() const { return mUp; }
  const XMFLOAT3& Right() const { return mRight; }

  XMVECTOR PositionVector() const { return XMLoadFloat3(&mPosition); }
  XMVECTOR DirectionVector() const { return XMLoadFloat3(&mDirection); }
  XMVECTOR UpVector() const { return XMLoadFloat3(&mUp); }
  XMVECTOR RightVector() const { return XMLoadFloat3(&mRight); }

  float FieldOfView() const { return mFieldOfView; }
  float AspectRatio() const { return mAspectRatio; }
  float NearPlaneDistance() const { return mNearPlaneDistance; }
  float FarPlaneDistance() const { return mFarPlaneDistance; }

  XMMATRIX ViewMatrix() const { return XMLoadFloat4x4(&mViewMatrix); }
  XMMATRIX ProjectionMatrix() const { return XMLoadFloat4x4(&mProjectionMatrix); }
  XMMATRIX ViewProjectionMatrix() const;

  virtual void SetPosition(FLOAT x, FLOAT y, FLOAT z);
  virtual void SetPosition(FXMVECTOR position);
  virtual void SetPosition(const XMFLOAT3& transform);

  virtual void Reset();
  virtual void Initialize() override;
  virtual void Update(const GameTime& game_time) override;
  virtual void UpdateViewMatrix();
  virtual void UpdateProjectionMatrix();
  void ApplyRotation(CXMMATRIX transform);
  void ApplyRotation(const XMFLOAT4X4& transform);

  static const float DefaultFieldOfView;
  static const float DefaultAspectRatio;
  static const float DefaultNearPlanceDistance;
  static const float DefaultFarPlaneDistance;

protected:
  float mFieldOfView;
  float mAspectRatio;
  float mNearPlaneDistance;
  float mFarPlaneDistance;

  XMFLOAT3 mPosition;
  XMFLOAT3 mDirection;
  XMFLOAT3 mUp;
  XMFLOAT3 mRight;

  XMFLOAT4X4 mViewMatrix;
  XMFLOAT4X4 mProjectionMatrix;

};

} // namespace Library