#pragma once
#include <vector>
#include <glm.hpp>

#include "JEngine/Shape/ShapeData.h"
namespace JEngine {
	class Teapot
	{
	private:
		//unsigned int faces;

		static void generatePatches(std::vector<float>& p,
			std::vector<float>& n,
			std::vector<float>& tc,
			std::vector<uint32_t>& el, int grid);
		static void buildPatchReflect(int patchNum,
			std::vector<float>& B, std::vector<float>& dB,
			std::vector<float>& v, std::vector<float>& n,
			std::vector<float>& tc, std::vector<uint32_t>& el,
			int& index, int& elIndex, int& tcIndex, int grid,
			bool reflectX, bool reflectY);
		static void buildPatch(glm::vec3 patch[][4],
			std::vector<float>& B, std::vector<float>& dB,
			std::vector<float>& v, std::vector<float>& n,
			std::vector<float>& tc, std::vector<uint32_t>& el,
			int& index, int& elIndex, int& tcIndex, int grid, glm::mat3 reflect,
			bool invertNormal);
		static void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);

		static void computeBasisFunctions(std::vector<float>& B, std::vector<float>& dB, int grid);
		static glm::vec3 evaluate(int gridU, int gridV, std::vector<float>& B, glm::vec3 patch[][4]);
		static glm::vec3 evaluateNormal(int gridU, int gridV, std::vector<float>& B, std::vector<float>& dB, glm::vec3 patch[][4]);
		static void moveLid(int grid, std::vector<float>& p, const glm::mat4& lidTransform);

	public:
		static void GetTeapot(ShapeData& shapedata, int grid);
	};
}