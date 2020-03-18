#include <JEngine.h>
#include <cstdio>

#include "gtx/transform.hpp"
#include "glm.hpp"

#include "imgui.h"

enum ShapeID{
	Teapot,Cube,Plane
};

class ExampleLayer : public JEngine::Layer {
public:
	ExampleLayer() :Layer("Example"){}

	void OnImGuiRender() override {
		ImGui::SetNextWindowSizeConstraints(ImVec2(500, 200), ImVec2(1000, 1000));
		ImGui::Begin("Light Setting"); 
		ImGui::SliderFloat("AmbientLight", &m_Light.AmbientLightScalar, 0.0f, 1.0f);
		ImGui::SliderFloat("DiffuseLight", &m_Light.DiffuseLightScalar, 0.0f, 1.0f);
		ImGui::SliderFloat("SpecularLight Radius", &m_Light.SpecularLightRadius, 0.0f, 30.0f);
		ImGui::SliderFloat("SpecularLight Pow", &m_Light.SpecularLightPow, 0.0f, 30.0f);	

		glm::vec3 p = m_Light.getLightPosition();
		float v[3] = { p.x,p.y,p.z };
		ImGui::DragFloat3("Light Position", v, 0.2f);
		m_Light.setLightPosition(v[0], v[1], v[2]);
		ImGui::End();

	}

	void OnAttach() override {
		m_shaders.Load(".\\asset\\ColorShader.glsl");
		m_shaders.Load(".\\asset\\LightCubeShader.glsl");

		m_Light.setLight({ -5.0f, 4.0f, 5.0f }, 0.2f, 0.6f, 6.0f, 20.0f);
		//m_Light.BindShader(m_shader);
		DrawShape(Teapot, JEngine::Shape::Teapot, 10);
		DrawShape(Cube, JEngine::Shape::Cube);
		DrawShape(Plane, JEngine::Shape::Plane, 40);
	}

	void OnUpdate(float dt) override {
		m_CameraController.OnUpdate(dt);
		glm::mat4 transform;
		JEngine::RenderCommand::Clear();
		JEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });

		JEngine::Renderer::BeginScene(m_CameraController.GetCamera(), m_Light);
		transform = glm::translate(glm::vec3(0.0f, 0.5f, 0.0f)) * glm::rotate(glm::radians(-90.0f),glm::vec3(1.0f,0.0f,0.0f));
		JEngine::Renderer::Submit(m_shaders.Get("ColorShader"), m_shape_VertexArray[Teapot], transform);


		transform = glm::translate(m_Light.getLightPosition()) * glm::scale(glm::vec3(0.3f, 0.3f, 0.3f));
		JEngine::Renderer::Submit(m_shaders.Get("LightCubeShader"), m_shape_VertexArray[Cube], transform);

		JEngine::Renderer::Submit(m_shaders.Get("ColorShader"), m_shape_VertexArray[Plane], glm::mat4(1.0f));

		JEngine::Renderer::EndScene();
	}

	void OnEvent(JEngine::Event& event) override {
		m_CameraController.OnEvent(event);
	}

	void DrawShape(int ShapeID, JEngine::Shape ShapeName,int val = 10) {
		m_shape_VertexArray[ShapeID].reset(JEngine::VertexArray::Create());

		JEngine::Ref<JEngine::VertexBuffer> vertexbuffer;
		JEngine::Ref<JEngine::IndexBuffer> indexbuffer;

		JEngine::ShapeData shape = JEngine::ShapeGenerator::makeShape(ShapeName,val);

		vertexbuffer.reset(JEngine::VertexBuffer::Create(shape));
		vertexbuffer->SetLayout({
				{"Position", JEngine::ShaderDataType::Float3},
				{"Color", JEngine::ShaderDataType::Float3},
				{"Normal", JEngine::ShaderDataType::Float3}
			});

		indexbuffer.reset(JEngine::IndexBuffer::Create(shape));

		m_shape_VertexArray[ShapeID]->AddVertexBuffer(vertexbuffer);
		m_shape_VertexArray[ShapeID]->AddIndexBuffer(indexbuffer);
		shape.CleanUp();
	}
private:
	JEngine::Ref<JEngine::VertexArray> m_shape_VertexArray[10];
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

