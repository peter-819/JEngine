#include "JEpch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace JEngine {

	RendererAPI::API Renderer::m_API = RendererAPI::API::OpenGL;

	void Renderer::BeginScene() {
		
	}

	void Renderer::EndScene() {

	}
	
	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexarray) {
		vertexarray->Bind();
		RenderCommand::DrawIndexed(vertexarray);
	}
}