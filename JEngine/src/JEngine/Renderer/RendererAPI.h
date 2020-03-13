#pragma once
#include "glm.hpp"
#include "JEngine/Renderer/VertexArray.h"
namespace JEngine {

	class RendererAPI {
	public:
		enum class API {
			None = 0,
			OpenGL = 1
		};
	
	public:
		virtual void SetViewpot(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexarray) = 0;

		inline API GetAPI() const { return s_API; }

	private:
		static API s_API;
	};

}