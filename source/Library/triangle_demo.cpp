#include "triangle_demo.hpp"
#include "game.hpp"
#include "game_exception.hpp"
#include "matrix_helper.hpp"
#include "color_helper.hpp"
#include "camera.hpp"
#include "utility.hpp"
#include "d3dcompiler.h"

namespace Rendering {

RTTI_DEFINITIONS(TriangleDemo)

TriangleDemo::TriangleDemo(Game& game, Camera& camera) : DrawableGameComponent(game, camera), mWorldMatrix(MatrixHelper::Identity) {}

TriangleDemo::~TriangleDemo() {
  ReleaseObject(mPass);
  ReleaseObject(mWvpVariable);
  ReleaseObject(mTechnique);
  ReleaseObject(mEffect);
  ReleaseObject(mInputLayout);
  ReleaseObject(mVertexBuffer);
}


void TriangleDemo::Initialize() {
  SetCurrentDirectory(Utility::ExecutableDirectory().c_str());

  UINT shader_flags = 0;

#if defined(_DEBUG) || defined (DEBUG)
  shader_flags |= D3DCOMPILE_DEBUG;
  shader_flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

  ID3D10Blob* compiled_shader = nullptr;
  ID3D10Blob* error_messages = nullptr;

  HRESULT hr = D3DCompileFromFile(L"Content\\Effects\\BasicEffect.fx", nullptr, nullptr, nullptr, "fx_5_0", shader_flags, 0, &compiled_shader, &error_messages);
  if (FAILED(hr)) {
    char* error_message = (error_messages != nullptr ? (char*)error_messages->GetBufferPointer() : "D3DX11CompileFromFile() failed.");
    GameException ex{ error_message, hr };
    ReleaseObject(error_messages);

    throw ex;
  }

  hr = D3DX11CreateEffectFromMemory(compiled_shader->GetBufferPointer(), compiled_shader->GetBufferSize(), 0, mGame->Direct3DDevice(), &mEffect);
  if (FAILED(hr))
    throw GameException("D3DX11CreateEffectFromMemory() failed.", hr);

  ReleaseObject(compiled_shader);

  mTechnique = mEffect->GetTechniqueByName("main11");
  if (mTechnique == nullptr)
    throw GameException("ID3DX11Effect::GetTechniqueByName() failed.");

  mPass = mTechnique->GetPassByName("p0");
  if (mTechnique == nullptr)
    throw GameException("ID3DX11EffectTechnique::GetPassByName() failed.");

  ID3DX11EffectVariable* variable = mEffect->GetVariableByName("WorldViewProjection");
  if (variable == nullptr)
    throw GameException("ID3DX11Effect::GetVariableByName() failed.");

  mWvpVariable = variable->AsMatrix();
  if (mWvpVariable->IsValid() == false)
    throw GameException("Invalid effect variable case.");

  D3DX11_PASS_DESC pass_desc;
  mPass->GetDesc(&pass_desc);

  D3D11_INPUT_ELEMENT_DESC input_element_desc[] = {
      { "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
      { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
  };

  if (FAILED(hr = mGame->Direct3DDevice()->CreateInputLayout(input_element_desc, ARRAYSIZE(input_element_desc), pass_desc.pIAInputSignature, pass_desc.IAInputSignatureSize, &mInputLayout)))
    throw GameException("ID3D11Device::CreateInputLayour() failed.", hr);

  BasicEffectVertex vertices[] = {
    BasicEffectVertex(XMFLOAT4(-1.0f, +1.0f, -1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::Green))),
    BasicEffectVertex(XMFLOAT4(+1.0f, +1.0f, -1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::Yellow))),
    BasicEffectVertex(XMFLOAT4(+1.0f, +1.0f, +1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::White))),
    BasicEffectVertex(XMFLOAT4(-1.0f, +1.0f, +1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::BlueGreen))),

    BasicEffectVertex(XMFLOAT4(-1.0f, -1.0f, +1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::Blue))),
    BasicEffectVertex(XMFLOAT4(+1.0f, -1.0f, +1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::Purple))),
    BasicEffectVertex(XMFLOAT4(+1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::Red))),
    BasicEffectVertex(XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT4(reinterpret_cast<const float*>(&ColorHelper::Black)))
  };

  D3D11_BUFFER_DESC vertex_buffer_desc;
  ZeroMemory(&vertex_buffer_desc, sizeof(vertex_buffer_desc));
  vertex_buffer_desc.ByteWidth = sizeof(BasicEffectVertex) * ARRAYSIZE(vertices);
  vertex_buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
  vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

  D3D11_SUBRESOURCE_DATA vertex_subresource_data;
  ZeroMemory(&vertex_subresource_data, sizeof(vertex_subresource_data));
  vertex_subresource_data.pSysMem = vertices;
  if (FAILED(mGame->Direct3DDevice()->CreateBuffer(&vertex_buffer_desc, &vertex_subresource_data, &mVertexBuffer)))
    throw GameException("ID3D11Device::CreateBuffer() failed.");

  UINT indices[] = {
    0, 1, 2,
    0, 2, 3,

    4, 5, 6,
    4, 6, 7,

    3, 2, 5,
    3, 5, 4,

    2, 1, 6,
    2, 6, 5,

    1, 7, 6,
    1, 0, 7,

    0, 3, 4,
    0, 4, 7
  };

  D3D11_BUFFER_DESC index_buffer_desc;
  ZeroMemory(&index_buffer_desc, sizeof(index_buffer_desc));
  index_buffer_desc.ByteWidth = sizeof(UINT) * ARRAYSIZE(indices);
  index_buffer_desc.Usage = D3D11_USAGE_IMMUTABLE;
  index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

  D3D11_SUBRESOURCE_DATA index_subresource_data;
  ZeroMemory(&index_subresource_data, sizeof(index_subresource_data));
  index_subresource_data.pSysMem = indices;
  if (FAILED(hr = mGame->Direct3DDevice()->CreateBuffer(&index_buffer_desc, &index_subresource_data, &mIndexBuffer)))
      throw GameException("ID3D11Device::CreateBuffer() failed.");
}

void TriangleDemo::Update(const GameTime& game_time) {
  mAngle += XM_PI *2* static_cast<float>(game_time.ElapsedGameTime());
  XMStoreFloat4x4(&mWorldMatrix, XMMatrixRotationX(mAngle));
}

void TriangleDemo::Draw(const GameTime& game_time) {
  ID3D11DeviceContext* direct3d_device_context = mGame->Direct3DDeviceContext();
  direct3d_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  direct3d_device_context->IASetInputLayout(mInputLayout);

  UINT stride = sizeof(BasicEffectVertex);
  UINT offset = 0;
  direct3d_device_context->IASetVertexBuffers(0, 1, &mVertexBuffer, &stride, &offset);
  direct3d_device_context->IASetIndexBuffer(mIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

  XMMATRIX world_matrix = XMLoadFloat4x4(&mWorldMatrix);
  XMMATRIX wvp = world_matrix * mCamera->ViewMatrix() * mCamera->ProjectionMatrix();
  mWvpVariable->SetMatrix(reinterpret_cast<const float*>(&wvp));

  mPass->Apply(0, direct3d_device_context);

  direct3d_device_context->DrawIndexed(36, 0, 0);
}

} // namespace Rendering