#pragma once

#include "drawable_game_component.hpp"

using namespace Library;

namespace Rendering {

class TriangleDemo : public DrawableGameComponent {
  RTTI_DECLARATIONS(TriangleDemo, DrawableGameComponent)

public:
  TriangleDemo() = delete;
  TriangleDemo(const TriangleDemo&) = delete;
  TriangleDemo(Game& game, Camera& camera);

  TriangleDemo& operator=(const TriangleDemo&) = delete;
  ~TriangleDemo();

  virtual void Initialize() override;
  virtual void Update(const GameTime& game_time) override;
  virtual void Draw(const GameTime& game_time) override;

private:
  struct BasicEffectVertex {
    XMFLOAT4 Position;
    XMFLOAT4 Color;
    
    BasicEffectVertex() {}

    BasicEffectVertex(XMFLOAT4 position, XMFLOAT4 color) : Position(position), Color(color) {}
  };

  ID3DX11Effect* mEffect = nullptr;
  ID3DX11EffectTechnique* mTechnique = nullptr;
  ID3DX11EffectPass* mPass = nullptr;
  ID3DX11EffectMatrixVariable* mWvpVariable = nullptr;

  ID3D11InputLayout* mInputLayout = nullptr;
  ID3D11Buffer* mVertexBuffer = nullptr;
  XMFLOAT4X4 mWorldMatrix;

  float mAngle = 0.0f;
}; // class TriangleDemo

} // namespace Rendering