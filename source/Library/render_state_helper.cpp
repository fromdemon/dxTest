#include "render_state_helper.hpp"
#include "game.hpp"

namespace Library {

RenderStateHelper::RenderStateHelper(Game& game) : mGame(game), mBlendfactor(new FLOAT[4]) {}

RenderStateHelper::~RenderStateHelper() {
  ReleaseObject(mRasterizerState);
  ReleaseObject(mBlendState);
  ReleaseObject(mDepthStencilState);
  DeleteObjects(mBlendfactor);
}

void RenderStateHelper::ResetAll(ID3D11DeviceContext* device_context) {
  device_context->RSSetState(nullptr);
  device_context->OMSetBlendState(nullptr, nullptr, UINT_MAX);
  device_context->OMSetDepthStencilState(nullptr, UINT_MAX);
}

void RenderStateHelper::SaveRasterizerState() {
  ReleaseObject(mRasterizerState);
  mGame.Direct3DDeviceContext()->RSGetState(&mRasterizerState);
}

void RenderStateHelper::RestoreRasterizerState() const {
  mGame.Direct3DDeviceContext()->RSSetState(mRasterizerState);
}

void RenderStateHelper::SaveBlendState() {
  ReleaseObject(mBlendState);
  mGame.Direct3DDeviceContext()->OMGetBlendState(&mBlendState, mBlendfactor, &mSampleMask);
}

void RenderStateHelper::RestoreBlendState() const {
  mGame.Direct3DDeviceContext()->OMSetBlendState(mBlendState, mBlendfactor, mSampleMask);
}

void RenderStateHelper::SaveDepthStencilState() {
  ReleaseObject(mDepthStencilState);
  mGame.Direct3DDeviceContext()->OMGetDepthStencilState(&mDepthStencilState, &mStencilRef);
}

void RenderStateHelper::RestoreDepthStencilState() const {
  mGame.Direct3DDeviceContext()->OMSetDepthStencilState(mDepthStencilState, mStencilRef);
}

void RenderStateHelper::RestoreAll() const {
  RestoreRasterizerState();
  RestoreBlendState();
  RestoreDepthStencilState();
}

void RenderStateHelper::SaveAll() {
  SaveRasterizerState();
  SaveBlendState();
  SaveDepthStencilState();
}

} // namespace Library