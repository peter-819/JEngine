#pragma once

#include "JEngine/Renderer/VertexArray.h"
namespace JEngine {
	class OpenGLVertexArray : public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexbuffer) override;
		virtual void AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexbuffer) override;
		
		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const { return m_VertexBuffers; };
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

	private:
		uint32_t m_VertexArrayID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}