#pragma once

#include <JEpch.h>

#ifdef JE_PLATFORM_WINDOWS
#include <Windows.h>
#endif


#include <JEngine/Core/core.h>
#include <JEngine/Events/Event.h>

namespace JEngine {

	enum class WINDOWAPI {
		NONE,WIN,GLFW
	};
	//WIN API TEST
#ifdef JE_PLATFORM_WINDOWS
	extern HINSTANCE J_hInstance;
	extern std::string J_ClassName;
#endif

	using EventCallbackFn = std::function<void(Event&)>;		//callback function pointer

	struct WindowProps {						//Window Class Props struct
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		
		WindowProps(
			const std::string &title = "JEngine Window",
			unsigned int width = 1200,
			unsigned int height = 720	
		): Title(title),Width(width),Height(height){
#ifdef JE_PLATFORM_WINDOWS
			hInstance = J_hInstance;
			Class = J_ClassName;
#endif
		}

#ifdef JE_PLATFORM_WINDOWS
		HINSTANCE hInstance;
		std::string Class;
#endif
	};

	struct WindowData {
		std::string Title;
		unsigned int Width, Height;
		bool VSync;
		EventCallbackFn EventCallback;
	};


	class JE_API Window {						//abstract window class
	public:
		virtual ~Window(){}
		virtual void OnUpdate() = 0;
		
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;					//vertical synchronization
		virtual bool IsVSync() const = 0;

		inline virtual void* GetNativeWindow() const = 0;
		static Window* Create(const WindowProps& props = WindowProps());
	};
}