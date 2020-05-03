#include "JEpch.h"

#include "WinApiGLContext.h"
#include <glad/glad.h>
#include "JEngine/Core/ErrorLogger.h"

namespace JEngine {

	WinApiGLContext::WinApiGLContext(HWND hwnd):m_hwnd(hwnd){

	}

	void WinApiGLContext::Init() {

		PIXELFORMATDESCRIPTOR pfd = {
				sizeof(PIXELFORMATDESCRIPTOR),  //  size of this pfd  
				1,                     // version number  
				PFD_DRAW_TO_WINDOW |   // support window  
					PFD_SUPPORT_OPENGL |  // support OpenGL  
					PFD_DOUBLEBUFFER,      // double buffered  
				PFD_TYPE_RGBA,         // RGBA type  
				24,                    // 24-bit color depth  
				0, 0, 0, 0, 0, 0,      // color bits ignored  
				0,                     // no alpha buffer  
				0,                     // shift bit ignored  
				0,                     // no accumulation buffer  
				0, 0, 0, 0,            // accum bits ignored  
				32,                    // 32-bit z-buffer      
				0,                     // no stencil buffer  
				0,                     // no auxiliary buffer  
				PFD_MAIN_PLANE,        // main layer  
				0,                     // reserved  
				0, 0, 0                // layer masks ignored  
		};

		m_dc = GetDC(m_hwnd);

		int pf = ChoosePixelFormat(m_dc, &pfd);
		SetPixelFormat(m_dc, pf, &pfd);

		m_rc = wglCreateContext(m_dc);
		wglMakeCurrent(m_dc, m_rc);

		gladLoadGL();
		JE_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
		JE_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
		JE_CORE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));

	}
	void WinApiGLContext::SwapBuffer() {
		SwapBuffers(m_dc);
	}

	WinApiGLContext::~WinApiGLContext() {
		ReleaseDC(m_hwnd, m_dc);
		wglDeleteContext(m_rc);
	}
}