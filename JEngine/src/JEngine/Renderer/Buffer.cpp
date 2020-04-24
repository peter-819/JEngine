#include "JEpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"


namespace JEngine {

	VertexBuffer* VertexBuffer::Create(void* vertices, uint32_t size) {

		RendererAPI::API a = Renderer::GetAPI();
		switch (a) {
		
		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		return nullptr;
	}


	IndexBuffer* IndexBuffer::Create(void* index, uint32_t count) {
		RendererAPI::API a = Renderer::GetAPI();
		switch (a) {

		case RendererAPI::API::None:
			JE_CORE_ASSERT(false, "Render API NONE");
			return nullptr;
		
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(index, count);
		}

		return nullptr;
	}

}