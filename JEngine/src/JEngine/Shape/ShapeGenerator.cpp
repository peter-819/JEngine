#include "JEpch.h"
#include "ShapeGenerator.h"
#include "ShapeData.h"
#include "asset/teapot.h"

namespace JEngine {
#define NUM_ELEMENTS_OF(x) sizeof(x)/sizeof(*x)

	using glm::vec3;
	ShapeData ShapeGenerator::makeTriangle() {
		Vertex verts[] = {
			glm::vec3(-1.0f, -1.0f, +0.0f),
			glm::vec3(+1.0f, +0.0f, +0.0f),

			glm::vec3(+0.0f, +1.0f, +0.0f),
			glm::vec3(+0.0f, +1.0f, +0.0f),

			glm::vec3(+1.0f, -1.0f, +0.0f),
			glm::vec3(+0.0f, +0.0f, +1.0f),
		};
		uint32_t ind[] = { 0,1,2 };

		ShapeData Tri;

		Tri.NumVertices = NUM_ELEMENTS_OF(verts);
		Tri.Vertices = new Vertex[Tri.NumVertices];
		memcpy(Tri.Vertices, verts, sizeof(verts));

		Tri.NumIndices = NUM_ELEMENTS_OF(ind);
		Tri.Indices = new uint32_t[Tri.NumIndices];
		memcpy(Tri.Indices, ind, sizeof(ind));

		return Tri;
	}

	vec3 getNormal(vec3 v1, vec3 v2, vec3 v3) {
		return glm::normalize(glm::cross(v2 - v1, v3 - v1));
	}

	ShapeData ShapeGenerator::makeCube() {
		vec3 vecs[] = {
			vec3(-1.0f, +1.0f, +1.0f), //1
			vec3(+1.0f, +0.0f, +0.0f), //
			vec3(+1.0f, +1.0f, +1.0f), //2
			vec3(+0.0f, +1.0f, +0.0f), //
			vec3(+1.0f, +1.0f, -1.0f), //3
			vec3(+0.0f, +0.0f, +1.0f), //
			vec3(-1.0f, +1.0f, -1.0f), //4
			vec3(+1.0f, +1.0f, +1.0f), //
									   //
			vec3(-1.0f, +1.0f, -1.0f), //5
			vec3(+1.0f, +0.0f, +1.0f), //
			vec3(+1.0f, +1.0f, -1.0f), //6
			vec3(+0.0f, +0.5f, +0.2f), //
			vec3(+1.0f, -1.0f, -1.0f), //7
			vec3(+0.8f, +0.6f, +0.4f), //
			vec3(-1.0f, -1.0f, -1.0f), //8
			vec3(+0.3f, +1.0f, +0.5f), //
									   //
			vec3(+1.0f, +1.0f, -1.0f), //9
			vec3(+0.2f, +0.5f, +0.2f), //
			vec3(+1.0f, +1.0f, +1.0f), //10
			vec3(+0.9f, +0.3f, +0.7f), //
			vec3(+1.0f, -1.0f, +1.0f), //11
			vec3(+0.3f, +0.7f, +0.5f), //
			vec3(+1.0f, -1.0f, -1.0f), //12
			vec3(+0.5f, +0.7f, +0.5f), //
									   //
			vec3(-1.0f, +1.0f, +1.0f), //13
			vec3(+0.7f, +0.8f, +0.2f), //
			vec3(-1.0f, +1.0f, -1.0f), //14
			vec3(+0.5f, +0.7f, +0.3f), //
			vec3(-1.0f, -1.0f, -1.0f), //15
			vec3(+0.4f, +0.7f, +0.7f), //
			vec3(-1.0f, -1.0f, +1.0f), //16
			vec3(+0.2f, +0.5f, +1.0f), //
									   //
			vec3(+1.0f, +1.0f, +1.0f), //17
			vec3(+0.6f, +1.0f, +0.7f), //
			vec3(-1.0f, +1.0f, +1.0f), //18
			vec3(+0.6f, +0.4f, +0.8f), //
			vec3(-1.0f, -1.0f, +1.0f), //19
			vec3(+0.2f, +0.8f, +0.7f), //
			vec3(+1.0f, -1.0f, +1.0f), //20
			vec3(+0.2f, +0.7f, +1.0f), //
									   //
			vec3(+1.0f, -1.0f, -1.0f), //21
			vec3(+0.8f, +0.3f, +0.7f), //
			vec3(-1.0f, -1.0f, -1.0f), //22
			vec3(+0.8f, +0.9f, +0.5f), //
			vec3(-1.0f, -1.0f, +1.0f), //23
			vec3(+0.5f, +0.8f, +0.5f), //
			vec3(+1.0f, -1.0f, +1.0f), //24
			vec3(+0.9f, +1.0f, +0.2f), //
		};
		uint32_t ind[] = {
			0  ,1  ,2,  0,  2,  3,
			4  ,5  ,6,  4,  6,  7,
			8  ,9  ,10, 8,  10, 11,
			12 ,13 ,14, 12, 14, 15,
			16 ,17 ,18, 16, 18, 19,
			20 ,22 ,21, 20, 23, 22,
		};
		Vertex * verts = new Vertex[24];
		ShapeData Shape;

		for (int i = 0; i < 6; i++) {
			int k = i * 4;
			vec3 nor = getNormal(vecs[(k) * 2], vecs[(k + 1) * 2], vecs[(k + 2) * 2]);
			for (int j = 0; j < 4; j++) {
				int temp = i * 4 + j;
				verts[temp].position = vecs[temp * 2];
				verts[temp].color = vecs[temp * 2 + 1];
				verts[temp].normal = nor;
			}
		}
		Shape.NumVertices = 24;
		Shape.Vertices = new Vertex[Shape.NumVertices];
		memcpy(Shape.Vertices, verts, sizeof(Vertex) * Shape.NumVertices);

		Shape.NumIndices = 36;
		Shape.Indices = new uint32_t[Shape.NumIndices];
		memcpy(Shape.Indices, ind, sizeof(uint32_t) * Shape.NumIndices);

		delete[] verts;

		return Shape;
	}

	void ShapeGenerator::getPlaneVertices(int dimension, uint32_t& Num, Vertex * &ver) {
		Num = dimension * dimension;
		ver = new Vertex[Num];
		int runner = 0, half = dimension / 2;
		for (int i = 0; i < dimension; i++)
			for (int j = 0; j < dimension; j++) {
				ver[runner].position = vec3(i - half, 0, j - half);
				ver[runner].color = vec3(1.0, 1.0, 0.0);
				ver[runner].normal = vec3(0.0, 1.0, 0.0);
				runner++;
			}

	}

	void ShapeGenerator::getPlaneIndices(int dimension, uint32_t& Num, uint32_t* &ind) {
		Num = (dimension - 1) * (dimension - 1) * 2 * 3;
		ind = new uint32_t[Num];
		int runner = 0;
		for (int i = 0; i < dimension - 1; i++)
			for (int j = 0; j < dimension - 1; j++) {
				ind[runner++] = i * dimension + j;
				ind[runner++] = i * dimension + j + 1;
				ind[runner++] = (i + 1) * dimension + j + 1;

				ind[runner++] = i * dimension + j;
				ind[runner++] = (i + 1) * dimension + j + 1;
				ind[runner++] = (i + 1) * dimension + j;
			}
	}

	ShapeData ShapeGenerator::makePlane(int dimension = 10) {
		ShapeData plane;
		getPlaneVertices(dimension, plane.NumVertices, plane.Vertices);
		getPlaneIndices(dimension, plane.NumIndices, plane.Indices);
		return plane;
	}

	ShapeData ShapeGenerator::makeTeapot(int grid) {
		ShapeData teapot;
		Teapot::GetTeapot(teapot, grid);
		return teapot;
	}

	ShapeData ShapeGenerator::makeShape(Shape shape,int val) {
		switch (shape) {
		case Shape::None:
			JE_CORE_ASSERT(false, "Invalid Shape!");
		case Shape::Plane:
			return makePlane(val);
		case Shape::Cube:
			return makeCube();
		case Shape::Teapot:
			return makeTeapot(val);
		case Shape::Triangle:
			return makeTriangle();
		}
		JE_CORE_ASSERT(false, "Invalid Shape!");
		exit(1);
	}
}