#pragma once
#include "Buffer.h"

namespace JEngine {
	class VertexArray {
	public:
		virtual ~VertexArray(){}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(Ref<VertexBuffer>& vertexbuffer) = 0;
		virtual void AddIndexBuffer(Ref<IndexBuffer>& indexbuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}