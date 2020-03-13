#include <JEpch.h>

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace JEngine {
	
	VertexArray* VertexArray::Create() {
		RendererAPI::API a = Renderer::GetAPI();
		switch (a) {
		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}
		return nullptr;
	}
}