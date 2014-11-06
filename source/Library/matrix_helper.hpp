#pragma once

#include "common.hpp"

namespace Library {

class MatrixHelper {
public:
  MatrixHelper() = delete;
  MatrixHelper(const MatrixHelper&) = delete;

  MatrixHelper& operator=(const MatrixHelper&) = delete;
  ~MatrixHelper() = default;

  static const XMFLOAT4X4 Identity;
  static const void GetForward(CXMMATRIX matrix, XMFLOAT3& vector);
  static const void GetUp(CXMMATRIX matrix, XMFLOAT3& vector);
  static const void GetRight(CXMMATRIX matrix, XMFLOAT3& vector);
  static const void GetTranslation(CXMMATRIX matrix, XMFLOAT3& vector);

  static const void SetForward(XMMATRIX& matrix, XMFLOAT3& forward);
  static const void SetUp(XMMATRIX& matrix, XMFLOAT3& up);
  static const void SetRight(XMMATRIX& matrix, XMFLOAT3& right);
  static const void SetTranslation(XMMATRIX& matrix, XMFLOAT3& translation);

}; // class MatrixHelper

} // namespace Library