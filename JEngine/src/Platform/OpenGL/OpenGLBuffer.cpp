#include "JEpch.h"

#include "OpenGLBuffer.h"

#include "glad/glad.h"

namespace JEngine {
	
	//--------------------------OpenGLVertexBuffer------------------------------//

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* vertices, uint32_t size) {
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	void OpenGLVertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLVertexBuffer::UnBind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//-----------------------------OpenGLIndexBuffer----------------------------//


	OpenGLIndexBuffer::OpenGLIndexBuffer(void* index, uint32_t count)
		:m_Count(count) {
		glCreateBuffers(1, &m_BufferID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), index, GL_STATIC_DRAW);
	}

	void OpenGLIndexBuffer::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void OpenGLIndexBuffer::UnBind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetCount() const {
		return m_Count;
	}
}