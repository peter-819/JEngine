#pragma once
#include "glm.hpp"

namespace JEngine {
	struct Vertex {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
	};
	
	struct ShapeData {
		Vertex* Vertices;
		uint32_t NumVertices;
		uint32_t* Indices;
		uint32_t NumIndices;

		uint32_t VerticesSize() const {
			return NumVertices * sizeof(Vertex);
		}

		uint32_t IndicesSize() const {
			return NumIndices * sizeof(uint32_t);
		}

		ShapeData():Vertices(nullptr),Indices(nullptr),NumVertices(0),NumIndices(0){}
		void CleanUp() {
			delete[] Vertices;
			delete[] Indices;
			NumVertices = NumIndices = 0;
		}
	};
}