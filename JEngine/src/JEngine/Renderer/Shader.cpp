#include "JEpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace JEngine{
	Shader* Shader::Create(const std::string& vertshader,const std::string& fragshader) {
		RendererAPI::API api = Renderer::GetAPI();

		switch (api) {
		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;
			
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertshader, fragshader);
		}
		return nullptr;
	}
	Shader* Shader::Create(const std::string& filepath) {
		RendererAPI::API api = Renderer::GetAPI();

		switch (api) {
		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}
		return nullptr;
	}
}