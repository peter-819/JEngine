#pragma once

#include "JEngine/Renderer/RendererAPI.h"

namespace JEngine {
	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetViewpot(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexarray) override;
	};
}