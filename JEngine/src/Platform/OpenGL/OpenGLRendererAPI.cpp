#include "JEpch.h"

#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace JEngine {
	void OpenGLRendererAPI::SetViewpot(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) {
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear() {
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);      //TODO: MOVE THIS
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexarray) {
		glDrawElements(GL_TRIANGLES, vertexarray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}