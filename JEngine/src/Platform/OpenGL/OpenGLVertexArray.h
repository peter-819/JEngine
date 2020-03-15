#pragma once

#include "JEngine/Renderer/VertexArray.h"
namespace JEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(Ref<VertexBuffer>& vertexbuffer) override;
		virtual void AddIndexBuffer(Ref<IndexBuffer>& indexbuffer) override;
		
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const { return m_VertexBuffers; };
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

	private:
		uint32_t m_VertexArrayID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}