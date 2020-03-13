#include "JEpch.h"

#include "OpenGLContext.h"
#include <glad/glad.h>

namespace JEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle)
		:m_WindowHandle(windowhandle){
	
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		JE_CORE_ASSERT(status, "failed to initialize GLAD!");

		JE_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
		JE_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		JE_CORE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));

	}

	void OpenGLContext::SwapBuffer() {
		glfwSwapBuffers(m_WindowHandle);
	}
}