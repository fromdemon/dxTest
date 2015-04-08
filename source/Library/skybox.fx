cbuffer CBufferPerObject {
  float4x4 WorldViewProjection : WORLDVIEWPROJECTION;
}

TextureCube SkyboxTexture;

SamplerState TrilinearSampler {
  Filter = MIN_MAG_MIP_LINEAR;
};

RasterizerState DisableCulling {
  CullMode = NONE;
};

struct VS_INPUT {
  float4 ObjectPosition : POSITION;
};

struct VS_OUTPUT {
  float4 Position :SV_Position;
  float3 TextureCoordinate : TEXCOORD;
};

VS_OUTPUT vertex_shader(VS_INPUT IN) {
  VS_OUTPUT OUT = (VS_OUTPUT)0;
  OUT.Position = mul(IN.ObjectPostion, WorldViewProjection);
  Out.TextureCoordinate = In.ObjectPosition.xyz;

  return OUT;
}

float4 pixel_shader(VS_OUTPUT IN) : SV_TARGET {
  return SkyboxTexture.Sample(TrilinearSampler, IN.TextureCoordinate);
}

technique11 main11 {
  pass p0 {
    SetVertexShader(CompileShader(vs_5_0, vertex_shader()));
    SetGeometryShader(NULL);
    SetPixelShader(CompileShader(ps_5_0, pixel_shader()));
    SetRasterizerState(DisableCulling);
  }
}