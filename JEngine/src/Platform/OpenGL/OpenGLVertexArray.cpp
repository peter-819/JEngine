#include <JEpch.h>

#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace JEngine {

	static GLenum GLShaderDataTypeToGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:      return GL_FLOAT;
		case ShaderDataType::Float2:     return GL_FLOAT;
		case ShaderDataType::Float3:     return GL_FLOAT;
		case ShaderDataType::Float4:     return GL_FLOAT;
		case ShaderDataType::Mat3:       return GL_FLOAT;
		case ShaderDataType::Mat4:       return GL_FLOAT;
		case ShaderDataType::Int:        return GL_INT;
		case ShaderDataType::Int2:       return GL_INT;
		case ShaderDataType::Int3:       return GL_INT;
		case ShaderDataType::Int4:       return GL_INT;
		case ShaderDataType::Bool:       return GL_BOOL;
		}
		JE_CORE_ASSERT(false, "invalid ShaderDataType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray() {
		glCreateVertexArrays(1, &m_VertexArrayID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_VertexArrayID);	
	}

	void OpenGLVertexArray::Unbind() const {
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexbuffer) {
		JE_CORE_ASSERT(vertexbuffer->GetLayout().GetBufferLayout().size(), "Can't Add VertexBuffer, It's Empty !!");
		glBindVertexArray(m_VertexArrayID);
		vertexbuffer->Bind();

		int i = 0;
		const auto& layout = vertexbuffer->GetLayout();
		
		for (const auto& e : layout) {
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i,
				e.GetComponentCount(),
				GLShaderDataTypeToGLBaseType(e.m_Type),
				e.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)e.m_Offset
			);
			i++;
		}
		m_VertexBuffers.push_back(vertexbuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexbuffer) {
		glBindVertexArray(m_VertexArrayID);
		indexbuffer->Bind();

		m_IndexBuffer = indexbuffer;
	}
}