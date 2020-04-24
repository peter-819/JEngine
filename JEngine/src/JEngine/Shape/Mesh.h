#pragma once
#include "glm.hpp"

#include "JEngine/Renderer/Shader.h"
#include "JEngine/Renderer/VertexArray.h"

#include <assimp/Importer.hpp>
namespace JEngine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
	};

	struct Index {
		uint32_t v0, v1, v2;
	};

	class SubMesh {
	public:
		uint32_t BaseVertex;
		uint32_t BaseIndex;
		uint32_t MaterialIndex;
		uint32_t IndexCount;

		glm::mat4 Transform;
	};

	class Mesh {
		friend class MeshGenerator;
	public:
		Mesh();
		Mesh(const std::string& filepath);
		void render(const glm::mat4& tran, Ref<Shader> shader);
	private:
		void SetVAO();
		std::vector<SubMesh> m_SubMesh;
		std::vector<Vertex> m_Vertices;
		std::vector<Index> m_Indices;
		Scope<Assimp::Importer> m_Importer;
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
	};
}