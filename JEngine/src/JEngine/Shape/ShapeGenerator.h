#pragma once
#include "ShapeData.h"

namespace JEngine {
	enum class Shape {
		None = 0,
		Cube,Plane,Teapot,Triangle
	};

	class ShapeGenerator
	{
	private:
		static void getPlaneVertices(int dimension, uint32_t& Num, Vertex*& ver);
		static void getPlaneIndices(int dimension, uint32_t& Num, uint32_t*& ind);
	public:
		static ShapeData makeTriangle();
		static ShapeData makeCube();
		static ShapeData makePlane(int dimension);
		static ShapeData makeTeapot(int grid);

		static ShapeData makeShape(Shape shape,int val = 10);
	};
}