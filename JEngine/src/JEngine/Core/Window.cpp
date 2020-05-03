#include "JEpch.h"
#include "Window.h"

#include "Platform/WinApi/WinApiWindow.h"
#include "Platform/Windows/WindowsWindow.h"

namespace JEngine {

	extern WINDOWAPI WindowAPI = WINDOWAPI::WIN;

#ifdef JE_PLATFORM_WINDOWS
	HINSTANCE J_hInstance;
	std::string J_ClassName;
#endif


	Window* Window::Create(const WindowProps& props) {
		switch (WindowAPI)
		{
		case JEngine::WINDOWAPI::NONE:
			JE_CORE_ASSERT(0, "WindowAPI NONE doesn't exist");
			return nullptr;
		case JEngine::WINDOWAPI::WIN:
			return new WinApiWindow(props);
		case JEngine::WINDOWAPI::GLFW:
			return new WindowsWindow(props);
		default:
			JE_CORE_ASSERT(0, "WindowAPI doesn't exist");
			return nullptr;
		}
		return nullptr;
	}
}