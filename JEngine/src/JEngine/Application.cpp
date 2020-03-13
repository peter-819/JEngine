#include <JEpch.h>

#include "Application.h"
#include "Log.h"
#include <glad/glad.h>
#include "Input.h"
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

	void Application::glTriangleTest() {
		std::shared_ptr<VertexBuffer> vertexbuffer;
		std::shared_ptr<IndexBuffer> indexbuffer;
		
		float verts[] = {
			-1.0f, -1.0f,
			+0.0f, +1.0f,
			+1.0f, -1.0f,
		};
		uint32_t ind[] = { 0,1,2 };

		vertexbuffer.reset(VertexBuffer::Create(verts,sizeof verts));
		vertexbuffer->SetLayout({
				{"Position", ShaderDataType::Float2}
			});

		indexbuffer.reset(IndexBuffer::Create(ind, 3));

		m_tri_VertexArray.reset(VertexArray::Create());
		m_tri_VertexArray->AddVertexBuffer(vertexbuffer);
		m_tri_VertexArray->AddIndexBuffer(indexbuffer);
		
		float sqverts[] = {
			-0.7f, -0.7f,
			-0.7f, +0.7f,
			+0.7f, +0.7f,
			+0.7f, -0.7f,
		};
		uint32_t sqind[] = { 0,1,2,2,3,0 };

		vertexbuffer.reset(VertexBuffer::Create(sqverts, sizeof sqverts));
		vertexbuffer->SetLayout({
				{ "Postion",ShaderDataType::Float2 } 
			});

		indexbuffer.reset(IndexBuffer::Create(sqind, 6));

		m_sq_VertexArray.reset(VertexArray::Create());
		m_sq_VertexArray->AddVertexBuffer(vertexbuffer);
		m_sq_VertexArray->AddIndexBuffer(indexbuffer);
	}

	Application::Application(){
		//Renderer::SetAPI(RenderAPI::OpenGL);

		JE_CORE_ASSERT(!s_Instance, "Already have a application");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(JE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);
	}

	void Application::OnEvent(Event& e) {
		JE_CORE_INFO("{0}", e.ToString());
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

		glTriangleTest();
		while (m_Running) {

			//glClear(GL_COLOR_BUFFER_BIT);
			RenderCommand::Clear();
			//glViewport(0,0,m_Window->GetWidth(), m_Window->GetHeight());
			RenderCommand::SetViewpot(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
			//m_sq_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_sq_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
			Renderer::BeginScene();
			Renderer::Submit(m_sq_VertexArray);
			Renderer::Submit(m_tri_VertexArray);
			Renderer::EndScene();
			//m_tri_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_tri_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
			
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

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