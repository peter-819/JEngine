#pragma once 

#include <Windows.h>

#include "JEngine/Renderer/GraphicContext.h"

namespace JEngine {

	class WinApiGLContext : public GraphicContext {

	public:
		WinApiGLContext(HWND hwnd);
		virtual void Init() override;
		virtual void SwapBuffer() override;
		virtual ~WinApiGLContext();
	private:
		HWND m_hwnd;
		HDC m_dc;
		HGLRC m_rc;
	};
}