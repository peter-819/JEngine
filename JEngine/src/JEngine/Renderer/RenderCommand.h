#pragma once

#include "RendererAPI.h"
#include "glm.hpp"
#include "VertexArray.h"

namespace JEngine {
	class RenderCommand {
	public:
		inline static void SetViewpot(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
			m_Api->SetViewpot(x, y, width, height);
		}
		inline static void SetClearColor(const glm::vec4& color) {
			m_Api->SetClearColor(color);
		}
		inline static void Clear() {
			m_Api->Clear();
		}
		inline static void DrawIndexed(const Ref<VertexArray>& vertexarray) {
			m_Api->DrawIndexed(vertexarray);
		}
		
	private:
		static RendererAPI* m_Api;
	};
}
