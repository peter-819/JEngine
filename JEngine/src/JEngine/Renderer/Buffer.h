#pragma once
#include "JEpch.h"

#include "BufferLayout.h"
namespace JEngine {

	class VertexBuffer {
	public:
		virtual ~VertexBuffer(){}
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(float* vertices,uint32_t size);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer(){}
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* index, uint32_t count);
	};
}