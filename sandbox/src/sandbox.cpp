#define _CRT_SECURE_NO_WARNINGS
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

		if (ImGui::Button("Add Light")) {
			m_Light[LightNum].setLight({ -5.0f, 4.0f, 5.0f }, 0.2f, 0.6f, 6.0f, 20.0f);
			LightNum++;
		}
		char str[100];
		for (int i = 0; i < LightNum; i++) {
			ImGui::Text("Light %d:", i);
			
			sprintf(str, "Light[%d].IsAbled", i);
			if (ImGui::Button(str)) m_Light[i].isAbled =!m_Light[i].isAbled;

			sprintf(str, "Light[%d].AmbientLight", i);
			ImGui::SliderFloat(str, &m_Light[i].AmbientLightScalar, 0.0f, 1.0f);

			sprintf(str, "Light[%d].DiffuseLight", i);
			ImGui::SliderFloat(str, &m_Light[i].DiffuseLightScalar, 0.0f, 1.0f);

			sprintf(str, "Light[%d].SpecularLight Radius", i);
			ImGui::SliderFloat(str, &m_Light[i].SpecularLightRadius, 0.0f, 30.0f);

			sprintf(str, "Light[%d].SpecularLight Pow", i);
			ImGui::SliderFloat(str, &m_Light[i].SpecularLightPow, 0.0f, 30.0f);
		
			glm::vec3 p = m_Light[i].getLightPosition();
			float v[3] = { p.x,p.y,p.z };
			sprintf(str, "Light[%d].Light Position", i);
			ImGui::DragFloat3(str, v, 0.2f);
			m_Light[i].setLightPosition(v[0], v[1], v[2]);
		}

		ImGui::End();
	}

	void OnAttach() override {
		m_shaders.Load(".\\asset\\ColorShader.glsl");
		m_shaders.Load(".\\asset\\LightCubeShader.glsl");

		m_Light[0].setLight({ -5.0f, 4.0f, 5.0f }, 0.2f, 0.6f, 6.0f, 20.0f);
		//m_Light.BindShader(m_shader);
		DrawShape(Teapot, JEngine::Shape::Teapot, 10);
		DrawShape(Cube, JEngine::Shape::Cube);
		DrawShape(Plane, JEngine::Shape::Plane, 40);
	}

	void setUniforms(JEngine::Ref<JEngine::Shader> shader) {
		shader->Bind();
		char str[100];
		for (int i = 0; i < LightNum; i++) {
			sprintf(str, "Light[%d].Position", i);
			shader->SetFloat3(str, m_Light[i].getLightPosition());
			sprintf(str, "Light[%d].Ambient", i);
			shader->SetFloat (str, m_Light[i].AmbientLightScalar);
			sprintf(str, "Light[%d].Diffuse", i);
			shader->SetFloat (str, m_Light[i].DiffuseLightScalar);
			sprintf(str, "Light[%d].Radius", i);
			shader->SetFloat (str, m_Light[i].SpecularLightRadius);
			sprintf(str, "Light[%d].Pow", i);
			shader->SetFloat (str, m_Light[i].SpecularLightPow);
			sprintf(str, "Light[%d].isAbled", i);
			shader->SetBool(str, m_Light[i].isAbled);
		}
	}

	void OnUpdate(float dt) override {
		m_CameraController.OnUpdate(dt);
		glm::mat4 transform;
		JEngine::RenderCommand::Clear();
		JEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });

		JEngine::Ref<JEngine::Shader> shader = m_shaders.Get("ColorShader");
		
		setUniforms(shader);

		JEngine::Renderer::BeginScene(m_CameraController.GetCamera());
		transform = glm::translate(glm::vec3(0.0f, 0.5f, 0.0f)) * glm::rotate(glm::radians(-90.0f),glm::vec3(1.0f,0.0f,0.0f));
		JEngine::Renderer::Submit(m_shaders.Get("ColorShader"), m_shape_VertexArray[Teapot], transform);

		for (int i = 0; i < LightNum; i++) {
			transform = glm::translate(m_Light[i].getLightPosition()) * glm::scale(glm::vec3(0.3f, 0.3f, 0.3f));
			JEngine::Renderer::Submit(m_shaders.Get("LightCubeShader"), m_shape_VertexArray[Cube], transform);
		}
		
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
	JEngine::Light m_Light[10];
	int LightNum = 1;
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

