#pragma once
#include "core.h"
#include "Window.h"
#include "JEngine/Events/Event.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "LayerStack.h"

#include "JEngine/ImGui/ImGuiLayer.h"

#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

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
		bool OnWindowClose(WindowCloseEvent& e);
		bool m_Running = true;
		
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
	
	private:
		std::shared_ptr<VertexArray> m_tri_VertexArray;

		std::shared_ptr<VertexArray> m_sq_VertexArray;
	private:
		static Application* s_Instance;
	};
	Application* createApplication();
}
