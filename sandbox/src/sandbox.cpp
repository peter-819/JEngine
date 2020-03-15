#include <JEngine.h>
#include <cstdio>

#include "gtx/transform.hpp"
#include "glm.hpp"

class ExampleLayer : public JEngine::Layer {
public:
	ExampleLayer() :Layer("Example"){}

	void OnAttach() override {

		m_shader.reset(JEngine::Shader::Create(".\\asset\\ColorShader.glsl"));
		JE_CLIENT_TRACE("{0}", m_shader->GetName());

		m_Light.setLight({ -10.0f, 3.0f, 6.0f }, 0.2f, 0.6f, 6.0f, 20.0f);
		//m_Light.BindShader(m_shader);
		DrawCube();
		DrawPlane();
	}

	void OnUpdate(float dt) override {
		m_CameraController.OnUpdate(dt);

		JEngine::RenderCommand::Clear();
		JEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });

		JEngine::Renderer::BeginScene(m_CameraController.GetCamera(), m_Light);
		JEngine::Renderer::Submit(m_shader,m_plane_VertexArray,glm::mat4(1.0f));
		JEngine::Renderer::Submit(m_shader, m_cube_VertexArray, glm::translate(glm::vec3(0.0f, 1.5f, 0.0f)));
		JEngine::Renderer::EndScene();
	}

	void OnEvent(JEngine::Event& event) override {
		m_CameraController.OnEvent(event);
	}

	void DrawCube() {
		m_cube_VertexArray.reset(JEngine::VertexArray::Create());

		JEngine::Ref<JEngine::VertexBuffer> vertexbuffer;
		JEngine::Ref<JEngine::IndexBuffer> indexbuffer;

		JEngine::ShapeData cube = JEngine::ShapeGenerator::makeCube();

		vertexbuffer.reset(JEngine::VertexBuffer::Create(cube));
		vertexbuffer->SetLayout({
				{"Position", JEngine::ShaderDataType::Float3},
				{"Color", JEngine::ShaderDataType::Float3},
				{"Normal", JEngine::ShaderDataType::Float3}
			});

		indexbuffer.reset(JEngine::IndexBuffer::Create(cube));

		m_cube_VertexArray->AddVertexBuffer(vertexbuffer);
		m_cube_VertexArray->AddIndexBuffer(indexbuffer);
		cube.CleanUp();
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
	JEngine::Ref<JEngine::VertexArray> m_cube_VertexArray;
	JEngine::Ref<JEngine::Shader> m_shader;
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

