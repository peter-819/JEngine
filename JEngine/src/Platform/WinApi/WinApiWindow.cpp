#include "JEpch.h"
#include "WinApiWindow.h"
#include "JEngine/Core/StringConverter.h"
#include "JEngine/Events/ApplicationEvent.h"

namespace JEngine {
	bool WAwindow::Initialize(WinApiWindow* winApiWindow,const WindowProps& props)
	{
		m_WinApiWindow = winApiWindow;
		m_hInstance = props.hInstance;
		m_WindowTitle = props.Title;
		m_WindowTitleWide = StringConverter::StringToWide(props.Title);
		m_WindowClass = props.Class;
		m_WindowClassWide = StringConverter::StringToWide(props.Class);
		m_Width = props.Width;
		m_Height = props.Height;

		RegisterWindowClass();

		m_Handle = CreateWindowEx(0,
			m_WindowClassWide.c_str(),
			m_WindowTitleWide.c_str(),
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			0,
			0,
			m_Width,
			m_Height,
			NULL,
			NULL,
			m_hInstance,
			m_WinApiWindow);

		if (m_Handle == NULL) {
			//ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed for Window: " + m_WindowTitle);
			JE_CORE_ASSERT(0, "CreateWindowEX Failed");
			return false;
		}

		ShowWindow(m_Handle, SW_SHOW);
		SetForegroundWindow(m_Handle);
		SetFocus(m_Handle);
		return true;
	}

	bool WAwindow::ProcessMessage()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(&msg, m_Handle, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_NULL) {
			if (!IsWindow(m_Handle)) {
				m_Handle = NULL;
				UnregisterClass(m_WindowClassWide.c_str(), m_hInstance);
				return false;
			}
		}
		return true;
	}

	WAwindow::~WAwindow()
	{
		if (m_Handle != NULL) {
			UnregisterClass(m_WindowClassWide.c_str(), m_hInstance);
			DestroyWindow(m_Handle);
		}
	}

	LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		WinApiWindow* const pWindow = reinterpret_cast<WinApiWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	
	LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_NCCREATE: {
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WinApiWindow* pWindow = reinterpret_cast<WinApiWindow*>(pCreate->lpCreateParams);
			if (pWindow == nullptr) {
				JE_CORE_ASSERT(0, "Pointer to WinApiWindow is null");
				exit(-1);
			}
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));

			pWindow->LoadGLContext(hwnd);

			return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	void WAwindow::RegisterWindowClass()
	{
		WNDCLASSEX wc;
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.lpfnWndProc = HandleMessageSetup;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = m_hInstance;
		wc.hIcon = NULL;
		wc.hIconSm = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = m_WindowClassWide.c_str();
		wc.cbSize = sizeof(WNDCLASSEX);
		RegisterClassEx(&wc);
	}

	//-----------------------Class WinApiWindow------------------------//

	WinApiWindow::WinApiWindow(const WindowProps& props) {
		Init(props);
	}

	WinApiWindow::~WinApiWindow() {
		Shutdown();
	}

	void WinApiWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		JE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		
		m_Window = new WAwindow();
		m_Window->Initialize(this,props);

	}

	LRESULT WinApiWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch (uMsg) {
		case WM_CLOSE: {
			DestroyWindow(hwnd);
			WindowCloseEvent e;
			m_Data.EventCallback(e);
			return 0;
		}
		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	void WinApiWindow::Shutdown() {
		delete m_Window;
		delete m_GLcontext;
	}

	void WinApiWindow::OnUpdate() {
		m_Window->ProcessMessage();
		m_GLcontext->SwapBuffer();
	}
	void WinApiWindow::SetVSync(bool enabled) {
		m_Data.VSync = enabled;
	}
	bool WinApiWindow::IsVSync() const {
		return m_Data.VSync;
	}

	void WinApiWindow::LoadGLContext(HWND hwnd) {
		m_GLcontext = new WinApiGLContext(hwnd);
		m_GLcontext->Init();
	}
}
