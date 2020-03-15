#include "JEpch.h"

#include "Renderer.h"
#include "RenderCommand.h"
#include "gtx/transform.hpp"

namespace JEngine {

	RendererAPI::API Renderer::m_API = RendererAPI::API::OpenGL;
	Scope<Renderer::SceneData> Renderer::m_SceneData = std::make_unique<Renderer::SceneData>();

	void Renderer::BeginScene(const ProjectiveCamera &camera, const Light& light) {
		m_SceneData->viewProjection = camera.GetMatrix();
		m_SceneData->CameraPosition = camera.GetPosition();

		m_SceneData->LightPosition = light.LightPosition;
		m_SceneData->AmbientLightScalar = light.AmbientLightScalar;
		m_SceneData->DiffuseLightScalar = light.DiffuseLightScalar;
		m_SceneData->SpecularLightRadius = light.SpecularLightRadius;
		m_SceneData->SpecularLightPow = light.SpecularLightPow;
	}

	void Renderer::EndScene() {

	}
	
	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewpot(0, 0, width, height);
	}

	void Renderer::Submit(const Ref<Shader>& shader,const Ref<VertexArray>& vertexarray,const glm::mat4& Transform) {
		shader->Bind();
		shader->SetMat4("FullMatrix", m_SceneData->viewProjection * Transform);
		shader->SetFloat3("CameraPosition", m_SceneData->CameraPosition);

		shader->SetFloat3("LightPosition", m_SceneData->LightPosition);
		shader->SetFloat("AmbientLightScalar", m_SceneData->AmbientLightScalar);
		shader->SetFloat("DiffuseLightScalar", m_SceneData->DiffuseLightScalar);
		shader->SetFloat("SpecularLightRadius", m_SceneData->SpecularLightRadius);
		shader->SetFloat("SpecularLightPow", m_SceneData->SpecularLightPow);

		shader->SetMat4("TransformMatrix", Transform);

		vertexarray->Bind();
		RenderCommand::DrawIndexed(vertexarray);
	}
}