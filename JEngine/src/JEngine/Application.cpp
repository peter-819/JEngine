#include <JEpch.h>

#include "Application.h"
#include "Log.h"
#include <glad/glad.h>
#include "Input.h"

namespace JEngine {

	Application* Application::s_Instance = nullptr;

	void Application::glTriangleTest() {
		float verts[] = {
			-1.0f, -1.0f,
			+0.0f, +1.0f,
			+1.0f, -1.0f,
		};
		GLushort ind[] = { 0,1,2 };

		GLuint VBID;
		glGenBuffers(1, &VBID);
		glBindBuffer(GL_ARRAY_BUFFER, VBID);
		glBufferData(GL_ARRAY_BUFFER, sizeof verts, verts, GL_STATIC_DRAW);

		GLuint EBID;
		glGenBuffers(1, &EBID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof ind, ind, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	}

	Application::Application(){
		JE_CORE_ASSERT(!s_Instance, "Already have a application");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(JE_BIND_EVENT_FN(Application::OnEvent));
		glTriangleTest();
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(JE_BIND_EVENT_FN(Application::OnWindowClose));
	
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer) {
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}

	void Application::AppRun() {
		while (m_Running) {
			glClear(GL_COLOR_BUFFER_BIT);
			glViewport(0,0,m_Window->GetWidth(), m_Window->GetHeight());
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();
			
			m_Window->OnUpdate();

		}
	}

	Application::~Application()	{
	}
}