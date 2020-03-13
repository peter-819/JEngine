#pragma once
#include "Buffer.h"

namespace JEngine {
	class VertexArray {
	public:
		virtual ~VertexArray(){}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexbuffer) = 0;
		virtual void AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexbuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();
	};
}