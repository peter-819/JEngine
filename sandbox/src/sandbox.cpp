#include <JEngine.h>
#include <cstdio>

#include "gtx/transform.hpp"
#include "glm.hpp"

class ExampleLayer : public JEngine::Layer {
public:
	ExampleLayer() :Layer("Example"){}

	void OnAttach() override {

		m_shaders.Load(".\\asset\\ColorShader.glsl");

		m_Light.setLight({ -5.0f, 4.0f, 5.0f }, 0.2f, 0.6f, 6.0f, 20.0f);
		//m_Light.BindShader(m_shader);
		DrawShape();
		DrawPlane();
	}

	void OnUpdate(float dt) override {
		m_CameraController.OnUpdate(dt);

		JEngine::RenderCommand::Clear();
		JEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });

		JEngine::Renderer::BeginScene(m_CameraController.GetCamera(), m_Light);
		JEngine::Renderer::Submit(m_shaders.Get("ColorShader"),m_plane_VertexArray,glm::mat4(1.0f));

		glm::mat4 transform = glm::translate(glm::vec3(0.0f, 0.5f, 0.0f)) * glm::rotate(glm::radians(-90.0f),glm::vec3(1.0f,0.0f,0.0f));

		JEngine::Renderer::Submit(m_shaders.Get("ColorShader"), m_shape_VertexArray, transform);
		JEngine::Renderer::EndScene();
	}

	void OnEvent(JEngine::Event& event) override {
		m_CameraController.OnEvent(event);
	}

	void DrawShape() {
		m_shape_VertexArray.reset(JEngine::VertexArray::Create());

		JEngine::Ref<JEngine::VertexBuffer> vertexbuffer;
		JEngine::Ref<JEngine::IndexBuffer> indexbuffer;

		JEngine::ShapeData shape = JEngine::ShapeGenerator::makeTeapot(1);

		vertexbuffer.reset(JEngine::VertexBuffer::Create(shape));
		vertexbuffer->SetLayout({
				{"Position", JEngine::ShaderDataType::Float3},
				{"Color", JEngine::ShaderDataType::Float3},
				{"Normal", JEngine::ShaderDataType::Float3}
			});

		indexbuffer.reset(JEngine::IndexBuffer::Create(shape));

		m_shape_VertexArray->AddVertexBuffer(vertexbuffer);
		m_shape_VertexArray->AddIndexBuffer(indexbuffer);
		shape.CleanUp();
	}

	void DrawPlane() {
		m_plane_VertexArray.reset(JEngine::VertexArray::Create());

		JEngine::Ref<JEngine::VertexBuffer> vertexbuffer;
		JEngine::Ref<JEngine::IndexBuffer> indexbuffer;

		JEngine::ShapeData plane = JEngine::ShapeGenerator::makePlane(40);

		vertexbuffer.reset(JEngine::VertexBuffer::Create(plane));
		vertexbuffer->SetLayout({
				{"Position", JEngine::ShaderDataType::Float3},
				{"Color", JEngine::ShaderDataType::Float3},
				{"Normal", JEngine::ShaderDataType::Float3}
			});

		indexbuffer.reset(JEngine::IndexBuffer::Create(plane));

		m_plane_VertexArray->AddVertexBuffer(vertexbuffer);
		m_plane_VertexArray->AddIndexBuffer(indexbuffer);
		plane.CleanUp();
	}
private:
	JEngine::Ref<JEngine::VertexArray> m_plane_VertexArray;
	JEngine::Ref<JEngine::VertexArray> m_shape_VertexArray;
	JEngine::ShaderLibrary m_shaders;
	JEngine::ProjectiveCameraController m_CameraController;
	JEngine::Light m_Light;
};

class sandbox : public JEngine::Application {
public:
	sandbox(){
		PushLayer(new ExampleLayer());
	}
	~sandbox(){}
};

JEngine::Application* JEngine::createApplication() {
	return new sandbox();
}

