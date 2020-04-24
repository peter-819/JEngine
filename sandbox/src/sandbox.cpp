#define _CRT_SECURE_NO_WARNINGS
#include <JEngine.h>

//-------  Main File Entry ------//
#include "JEngine/EntryPoint.h"


enum ShapeID{
	Teapot,Cube,Plane,FileShape
};

class ExampleLayer : public JEngine::Layer {
public:
	ExampleLayer() :Layer("Example"),m_Mesh(".\\asset\\Donut2.fbx"){}

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
		m_Plane = JEngine::MeshGenerator::makePlane(50);
		m_Cube = JEngine::MeshGenerator::makeCube();
		//m_Light.BindShader(m_shader);

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

		for (int i = 0; i < LightNum; i++) {
			transform = glm::translate(m_Light[i].getLightPosition()) * glm::scale(glm::vec3(0.3f, 0.3f, 0.3f));
			m_Cube->render(transform, m_shaders.Get("LightCubeShader"));
		}

		transform = glm::translate(glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::scale(glm::vec3(10.0f, 10.0f, 10.0f))
			* glm::rotate(-glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		m_Mesh.render(transform, m_shaders.Get("ColorShader"));
		m_Plane->render(glm::mat4(1.0f), m_shaders.Get("ColorShader"));

		JEngine::Renderer::EndScene();
	}

	void OnEvent(JEngine::Event& event) override {
		m_CameraController.OnEvent(event);
	}
private:
	JEngine::Mesh m_Mesh;
	JEngine::Ref<JEngine::Mesh> m_Plane, m_Cube;
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

