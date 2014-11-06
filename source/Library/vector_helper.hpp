#pragma once

#include "common.hpp"

namespace Library {

class Vector2Helper {
public:
  Vector2Helper() = delete;
  Vector2Helper(const Vector2Helper&) = delete;

  Vector2Helper& operator=(const Vector2Helper&) = delete;
  ~Vector2Helper() = default;

  static const XMFLOAT2 Zero;
  static const XMFLOAT2 One;

  static std::string ToString(const XMFLOAT2& vector);
}; // class Vector2Helper

class Vector3Helper {
public:
  Vector3Helper() = delete;
  Vector3Helper(const Vector3Helper&) = delete;

  Vector3Helper& operator=(const Vector3Helper&) = delete;
  ~Vector3Helper() = default;

  static const XMFLOAT3 Zero;
  static const XMFLOAT3 One;
  static const XMFLOAT3 Up;
  static const XMFLOAT3 Down;
  static const XMFLOAT3 Right;
  static const XMFLOAT3 Left;
  static const XMFLOAT3 Forward;
  static const XMFLOAT3 Backward;

  static std::string ToString(const XMFLOAT3& vector);
}; // class Vector3Helper

class Vector4Helper {
public:
  Vector4Helper() = delete;
  Vector4Helper(const Vector4Helper&) = delete;

  Vector4Helper& operator=(const Vector4Helper&) = delete;
  ~Vector4Helper() = default;

  static const XMFLOAT4 Zero;
  static const XMFLOAT4 One;

  std::string ToString(const XMFLOAT4& vector);
}; // class Vector4Helper

} // namespace Library