#include "JEpch.h"

#include "Renderer.h"
#include "RenderCommand.h"
#include "gtx/transform.hpp"

namespace JEngine {

	RendererAPI::API Renderer::m_API = RendererAPI::API::OpenGL;
	std::unique_ptr<Renderer::SceneData> Renderer::m_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::BeginScene(const ProjectiveCamera &camera) {
		m_SceneData->viewProjection = camera.GetMatrix();
	}

	void Renderer::EndScene() {

	}
	
	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewpot(0, 0, width, height);
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexarray) {
		shader->Bind();
		shader->SetMat4("fullMatrix", m_SceneData->viewProjection);
				
		vertexarray->Bind();
		RenderCommand::DrawIndexed(vertexarray);
	}
}