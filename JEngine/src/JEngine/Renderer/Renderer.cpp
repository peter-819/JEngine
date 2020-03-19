#include "JEpch.h"

#include "Renderer.h"
#include "RenderCommand.h"
#include "gtx/transform.hpp"

namespace JEngine {

	RendererAPI::API Renderer::m_API = RendererAPI::API::OpenGL;
	Scope<Renderer::SceneData> Renderer::m_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::BeginScene(const ProjectiveCamera &camera, const Light& light) {
		m_SceneData->camera = camera;
		m_SceneData->lights.push_back(light);
	}
	
	void Renderer::BeginScene(const ProjectiveCamera& camera) {
		m_SceneData->camera = camera;
	}

	void Renderer::EndScene() {

	}
	
	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewpot(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexarray,const glm::mat4& Transform) {
		shader->Bind();

		shader->SetFloat3("CameraPosition", m_SceneData->camera.GetPosition());

		shader->SetMat4("TransformMatrix", Transform);
		shader->SetMat4("CameraMatrix", m_SceneData->camera.GetCameraMatrix());
		shader->SetMat4("ProjectionMatrix", m_SceneData->camera.GetProjectMatrix());

		vertexarray->Bind();
		RenderCommand::DrawIndexed(vertexarray);
	}
}