#pragma once
#include "JEpch.h"

#include "JEngine/Renderer/Buffer.h"

namespace JEngine {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:

		OpenGLVertexBuffer(void* verices, uint32_t size);

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(const BufferLayout& layout) override { m_BufferLayout = layout; };
		virtual const BufferLayout& GetLayout() const override { return m_BufferLayout; };

	private:
		BufferLayout m_BufferLayout;
		uint32_t m_BufferID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:

		OpenGLIndexBuffer(void* index, uint32_t count);

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32_t GetCount() const override;
	private:
		uint32_t m_BufferID;
		uint32_t m_Count;
	};
}