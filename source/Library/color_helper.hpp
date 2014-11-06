#pragma once

#include "common.hpp"

namespace Library {

class ColorHelper {
public:
  ColorHelper() = delete;
  ColorHelper(const ColorHelper&) = delete;

  ColorHelper& operator=(const ColorHelper&) = delete;
  ~ColorHelper() = default;

  static const XMVECTORF32 Black;
  static const XMVECTORF32 White;
  static const XMVECTORF32 Red;
  static const XMVECTORF32 Green;
  static const XMVECTORF32 Blue;
  static const XMVECTORF32 Yellow;
  static const XMVECTORF32 BlueGreen;
  static const XMVECTORF32 Purple;
  static const XMVECTORF32 CornflowerBlue;
  static const XMVECTORF32 Wheat;
  static const XMVECTORF32 LightGray;
}; // class ColorHelper

} // namespace Library