#include <JEpch.h>

#include "Application.h"
#include "JEngine/Core/Log.h"
#include <glad/glad.h>
#include "JEngine/Core/Input.h"
#include "JEngine/Renderer/BufferLayout.h"
#include "JEngine/Renderer/RenderCommand.h"

namespace JEngine {

	Application* Application::s_Instance = nullptr;

	static GLenum GLShaderDataTypeToGLBaseType(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:      return GL_FLOAT;
		case ShaderDataType::Float2:     return GL_FLOAT;
		case ShaderDataType::Float3:     return GL_FLOAT;
		case ShaderDataType::Float4:     return GL_FLOAT;
		case ShaderDataType::Mat3:       return GL_FLOAT;
		case ShaderDataType::Mat4:       return GL_FLOAT;
		case ShaderDataType::Int:        return GL_INT;
		case ShaderDataType::Int2:       return GL_INT;
		case ShaderDataType::Int3:       return GL_INT;
		case ShaderDataType::Int4:       return GL_INT;
		case ShaderDataType::Bool:       return GL_BOOL;
		}
		JE_CORE_ASSERT(false, "invalid ShaderDataType");
		return 0;
	}


	Application::Application(){
		ts = TimeStep::Create();
		ts->Init();

		JE_CORE_ASSERT(!s_Instance, "Already have a application");
		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(JE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(JE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(JE_BIND_EVENT_FN(Application::OnWindowResize));

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

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
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
			ts->GetNewFrame();
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts->GetDeltaTime());

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}

	Application::~Application()	{
	}
}