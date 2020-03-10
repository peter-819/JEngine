#pragma once
#include "core.h"
#include "Window.h"
#include "JEngine/Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "LayerStack.h"

namespace JEngine {
	class JE_API Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void run() {}

		void glTriangleTest();
		void AppRun();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		LayerStack m_LayerStack;
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		std::unique_ptr<Window> m_Window;

	private:
		static Application* s_Instance;
	};
	Application* createApplication();
}
