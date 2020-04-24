#pragma once
#include <vector>

#include "glm.hpp"
#include "JEngine/Core/core.h"
#include "JEngine/Shape/ShapeData.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>

static const uint32_t s_MeshImportFlags =
	aiProcess_CalcTangentSpace |        // Create binormals/tangents just in case
	aiProcess_Triangulate |             // Make sure we're triangles
	aiProcess_SortByPType |             // Split meshes by primitive type
	aiProcess_GenNormals |              // Make sure we have legit normals
	aiProcess_GenUVCoords |             // Convert UVs if required 
	aiProcess_OptimizeMeshes |          // Batch draws where possible
	aiProcess_ValidateDataStructure;    // Validation

class SubMesh {
public:
	uint32_t BaseVertex;
	uint32_t BaseIndex;
	uint32_t MaterialIndex;
	uint32_t IndexCount;

	glm::mat4 Transform;
};
class Mesh {
public:
	Mesh(const std::string& filename) {
		m_Importer = std::make_unique<Assimp::Importer>();
		const aiScene* scene = m_Importer->ReadFile(filename, s_MeshImportFlags);

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
				m_Indices.push_back(mesh->mFaces[i].mIndices[0]);
				m_Indices.push_back(mesh->mFaces[i].mIndices[1]);
				m_Indices.push_back(mesh->mFaces[i].mIndices[2]);
			}
		}
		m_ShapeData.NumVertices = m_Vertices.size();
		m_ShapeData.Vertices = new JEngine::Vertex[m_ShapeData.NumVertices];
		std::copy(m_Vertices.begin(), m_Vertices.begin()+m_ShapeData.NumVertices, m_ShapeData.Vertices);

		m_ShapeData.NumIndices = m_Indices.size();
		m_ShapeData.Indices = new uint32_t[m_ShapeData.NumIndices];
		std::copy(m_Indices.begin(), m_Indices.begin() + m_ShapeData.NumIndices, m_ShapeData.Indices);

	}
	JEngine::ShapeData GetShape() {
		return m_ShapeData;
	}
private:
	std::vector<SubMesh> m_SubMesh;
	std::vector<JEngine::Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
	JEngine::Scope<Assimp::Importer> m_Importer;
	JEngine::ShapeData m_ShapeData;
};