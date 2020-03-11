#pragma once 

#include "GLFW/glfw3.h"
#include "GraphicContext.h"

namespace JEngine {
	
	class OpenGLContext : public GraphicContext {
	
	public:
		OpenGLContext(GLFWwindow* windowhandle);
		virtual void Init() override;
		virtual void SwapBuffer() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}