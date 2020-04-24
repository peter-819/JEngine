#pragma once
#include "Mesh.h"

namespace JEngine {
	enum class MeshType {
		None = 0,
		Cube,Plane,Teapot,Triangle
	};

	class MeshGenerator
	{
	private:
		static void getPlaneVertices(int dimension, std::vector<Vertex> &ver);
		static void getPlaneIndices(int dimension, std::vector<Index> &ind);
	public:
		static Ref<Mesh> makeCube();
		static Ref<Mesh> makePlane(int dimension);
	};
}