#pragma once

#include "common.hpp"

struct aiMesh;

namespace Library {

  class Material;
  class ModelMaterial;

  class Mesh {
    friend class Model;

  public:
    Mesh(Model& model, ModelMaterial* material);
    Mesh(const Mesh&) = delete;

    Mesh& operator=(const Mesh&) = delete;
    ~Mesh();

    Model& GetModel() { return model_; }
    ModelMaterial* GetMaterial() { return material_; }

    const std::vector<XMFLOAT3>& Vertices() const { return vertices_; }
    const std::vector<XMFLOAT3>& Normals() const { return normals_; }
    const std::vector<XMFLOAT3>& Tangents() const { return tangents_; }
    const std::vector<XMFLOAT3>& BiNormals() const { return bi_normals_; }
    const std::vector<std::vector<XMFLOAT3>> TextureCoordinates() const { return texture_coordinates_; }
    const std::vector<std::vector<XMFLOAT4>> VertexCoordinates() const { return vertex_coordinates_; }
    UINT FaceCount() const { return face_count_; }
    std::vector<UINT> Indices() const { return indices_; }

    void CreateIndexBuffer(ID3D11Buffer** index_buffer);

  private:
    Mesh(Model& model, aiMesh& mesh);

    Model& model_;
    ModelMaterial* material_;
    std::string name_;
    std::vector<XMFLOAT3> vertices_;
    std::vector<XMFLOAT3> normals_;
    std::vector<XMFLOAT3> tangents_;
    std::vector<XMFLOAT3> bi_normals_;
    std::vector<std::vector<XMFLOAT3>> texture_coordinates_;
    std::vector<std::vector<XMFLOAT4>> vertex_coordinates_;
    UINT face_count_ = 0;
    std::vector<UINT> indices_;
  }; // class Mesh

} // namespace Library