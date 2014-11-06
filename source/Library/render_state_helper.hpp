#pragma once

#include "common.hpp"

namespace Library {

class Game;

class RenderStateHelper {
public:
  RenderStateHelper() = delete;
  RenderStateHelper(const RenderStateHelper&) = delete;
  RenderStateHelper(Game& game);
  ~RenderStateHelper();

  RenderStateHelper& operator=(const RenderStateHelper&) = delete;

  static void ResetAll(ID3D11DeviceContext* device_context);

  ID3D11RasterizerState* RasterizerState();
  ID3D11BlendState* BlendState();
  ID3D11DepthStencilState* DepthStencilState();

  void SaveRasterizerState();
  void RestoreRasterizerState() const;

  void SaveBlendState();
  void RestoreBlendState() const;

  void SaveDepthStencilState();
  void RestoreDepthStencilState() const;

  void SaveAll();
  void RestoreAll() const;

private:
  Game& mGame;

  ID3D11RasterizerState* mRasterizerState = nullptr;
  ID3D11BlendState* mBlendState = nullptr;
  ID3D11DepthStencilState* mDepthStencilState = nullptr;
  FLOAT* mBlendfactor;
  UINT mSampleMask = UINT_MAX;
  UINT mStencilRef = UINT_MAX;
};

} // namespace Library