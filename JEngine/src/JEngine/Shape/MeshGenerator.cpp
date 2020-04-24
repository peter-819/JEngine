#include "JEpch.h"
#include "MeshGenerator.h"
#include "Mesh.h"

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/DefaultLogger.hpp>
#include <assimp/LogStream.hpp>
namespace JEngine {
#define NUM_ELEMENTS_OF(x) sizeof(x)/sizeof(*x)

	using glm::vec3;

	vec3 getNormal(vec3 v1, vec3 v2, vec3 v3) {
		return glm::normalize(glm::cross(v2 - v1, v3 - v1));
	}

	Ref<Mesh> MeshGenerator::makeCube() {
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
		Ref<Mesh> mesh;
		mesh.reset(new Mesh());

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
		mesh->m_Vertices.resize(24);
		mesh->m_Indices.resize(12);
		std::copy(verts, verts + 24, mesh->m_Vertices.begin());
		std::copy((Index*)ind, (Index*)ind + 12, mesh->m_Indices.begin());
		mesh->SetVAO();

		delete[] verts;
		
		return mesh;
	}

	void MeshGenerator::getPlaneVertices(int dimension, std::vector<Vertex> &ver) {
		int Num = dimension * dimension;
		int half = dimension / 2;
		for (int i = 0; i < dimension; i++)
			for (int j = 0; j < dimension; j++) {
				Vertex v;
				v.position = vec3(i - half, 0, j - half);
				v.color = vec3(1.0, 1.0, 0.0);
				v.normal = vec3(0.0, 1.0, 0.0);
				ver.push_back(v);
			}
	}

	void MeshGenerator::getPlaneIndices(int dimension, std::vector<Index> &ind) {
		int Num = (dimension - 1) * (dimension - 1) * 2 * 3;
		int runner = 0;
		for (int i = 0; i < dimension - 1; i++)
			for (int j = 0; j < dimension - 1; j++) {
				Index a, b;
				a.v0 = i * dimension + j;
				a.v1 = i * dimension + j + 1;
				a.v2 = (i + 1) * dimension + j + 1;

				b.v0 = i * dimension + j;
				b.v1 = (i + 1) * dimension + j + 1;
				b.v2 = (i + 1) * dimension + j;
				ind.push_back(a);
				ind.push_back(b);
			}

	}

	Ref<Mesh> MeshGenerator::makePlane(int dimension = 10) {
		Ref<Mesh> mesh;
		mesh.reset(new Mesh());

		getPlaneVertices(dimension, mesh->m_Vertices);
		getPlaneIndices(dimension, mesh->m_Indices);
		mesh->SetVAO();
		
		return mesh;
	}

}