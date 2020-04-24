#include "JEpch.h"
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

#include "JEngine/Renderer/Buffer.h"
#include "JEngine/Renderer/Renderer.h"

namespace JEngine {

	static const uint32_t s_MeshImportFlags =
		aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
		aiProcess_Triangulate |             // Make sure we're triangles
		aiProcess_SortByPType |             // Split meshes by primitive type
		aiProcess_GenNormals |              // Make sure we have legit normals
		aiProcess_GenUVCoords |             // Convert UVs if required 
		aiProcess_OptimizeMeshes |          // Batch draws where possible
		aiProcess_ValidateDataStructure;    // Validation

	Mesh::Mesh() {

	}

	Mesh::Mesh(const std::string& filepath) {
		m_Importer = std::make_unique<Assimp::Importer>();
		const aiScene* scene = m_Importer->ReadFile(filepath, s_MeshImportFlags);

		m_SubMesh.reserve(scene->mNumMeshes);

		uint32_t vertexCount = 0;
		uint32_t indexCount = 0;
		for (size_t m = 0; m < scene->mNumMeshes; m++) {
			aiMesh* mesh = scene->mMeshes[m];

			SubMesh submesh;
			submesh.BaseVertex = vertexCount;
			submesh.BaseIndex = indexCount;
			submesh.MaterialIndex = mesh->mMaterialIndex;
			submesh.IndexCount = mesh->mNumFaces * 3;
			m_SubMesh.push_back(submesh);

			vertexCount += mesh->mNumVertices;
			indexCount += submesh.IndexCount;

			JE_CLIENT_ASSERT(mesh->HasPositions(), "Meshes require positions");
			JE_CLIENT_ASSERT(mesh->HasNormals(), "Meshes require normals");

			for (size_t i = 0; i < mesh->mNumVertices; i++) {
				JEngine::Vertex vertex;
				vertex.position = { mesh->mVertices[i].x, mesh->mVertices[i].y,mesh->mVertices[i].z };
				vertex.normal = { mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z };
				vertex.color = { 0.9,0.9,0.9 };
				m_Vertices.push_back(vertex);
			}
			for (size_t i = 0; i < mesh->mNumFaces; i++) {
				m_Indices.push_back({
					mesh->mFaces[i].mIndices[0],
					mesh->mFaces[i].mIndices[1],
					mesh->mFaces[i].mIndices[2] });
			}
		}
		SetVAO();
	}

	void Mesh::SetVAO() {
		m_VertexArray.reset(VertexArray::Create());
		Ref<VertexBuffer> vertexBuffer;
		Ref<IndexBuffer> indexBuffer;

		vertexBuffer.reset(VertexBuffer::Create(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex)));
		vertexBuffer->SetLayout({
				{"Position", JEngine::ShaderDataType::Float3},
				{"Color", JEngine::ShaderDataType::Float3},
				{"Normal", JEngine::ShaderDataType::Float3}
			});
		indexBuffer.reset(IndexBuffer::Create(m_Indices.data(), m_Indices.size() * 3));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->AddIndexBuffer(indexBuffer);
	}

	void Mesh::render(const glm::mat4& tran  , Ref<Shader> shader) {
		m_Shader = shader;
		Renderer::Submit(shader, m_VertexArray, tran);
	}
}