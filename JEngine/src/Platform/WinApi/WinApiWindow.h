#pragma once
#include <Windows.h>

#include "JEngine/Core/Window.h"
#include "WinApiGLContext.h"
namespace JEngine {
	class WinApiWindow;
	class WAwindow {
	public:
		bool Initialize(WinApiWindow* winApiWindow,const WindowProps& props);
		bool ProcessMessage();
		~WAwindow();
	private:
		void RegisterWindowClass();

		HWND m_Handle = NULL;
		HINSTANCE m_hInstance = NULL;
		std::string m_WindowTitle = "";
		std::wstring m_WindowTitleWide = L"";
		std::string m_WindowClass = "";
		std::wstring m_WindowClassWide = L"";
		int m_Width = 0;
		int m_Height = 0;
		WinApiWindow* m_WinApiWindow;
	};

	class WinApiWindow : public Window {
	public:
		WinApiWindow(const WindowProps& props);
		virtual ~WinApiWindow();
		
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override {
			m_Data.EventCallback = callback;
		}
		void OnUpdate() override;

		LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const override { return m_Window; }
		void LoadGLContext(HWND hwnd);
	private:
		void Init(const WindowProps& props);
		void Shutdown();

		WindowData m_Data;
		WAwindow* m_Window;
		WinApiGLContext* m_GLcontext;
	};
}