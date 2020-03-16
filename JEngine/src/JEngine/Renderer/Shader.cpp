#include "JEpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace JEngine{
	Ref<Shader> Shader::Create(const std::string& name,const std::string& vertshader,const std::string& fragshader) {
		RendererAPI::API api = Renderer::GetAPI();

		switch (api) {
		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;
			
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, vertshader, fragshader);
		}
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath) {
		RendererAPI::API api = Renderer::GetAPI();

		switch (api) {
		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		}
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name,const std::string& filepath) {
		RendererAPI::API api = Renderer::GetAPI();

		switch (api) {
		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name, filepath);
		}
		return nullptr;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		JE_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader Exists !");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(name, filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name) {
		JE_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Invalid Shader Name");
		return m_Shaders[name];
	}

}