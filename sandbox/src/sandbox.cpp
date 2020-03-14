#include <JEngine.h>
#include <cstdio>

class ExampleLayer : public JEngine::Layer {
public:
	ExampleLayer() :Layer("Example"){}

	void OnAttach() override {
		glTriangleTest();
	}

	void OnUpdate(float dt) override {
		m_CameraController.OnUpdate(dt);

		JEngine::RenderCommand::Clear();
		JEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });

		JEngine::Renderer::BeginScene(m_CameraController.GetCamera());
		//JEngine::Renderer::Submit(m_sq_VertexArray);
		JEngine::Renderer::Submit(m_cube_shader,m_cube_VertexArray);
		JEngine::Renderer::EndScene();
	}

	void OnEvent(JEngine::Event& event) override {
		//JE_CLIENT_TRACE("{0}", event.ToString());
		m_CameraController.OnEvent(event);
	}

	void glTriangleTest() {

		std::string vertshader = R"(
			#version 430
			
			in layout(location=0) vec3 position;
			in layout(location=1) vec3 color;
			in layout(location=2) vec3 normal;

			uniform mat4 fullMatrix;
			
			out vec3 theColor;
			
			void main(){
				vec4 v = vec4(position,1.0);
				gl_Position =  fullMatrix * v;
				theColor = color;
			}
		)";

		std::string fragshader = R"(
			#version 430
			
			in vec3 theColor;
			
			out vec4 daColor;
			
			void main(){
				daColor = vec4(theColor,1.0);	
			}
		)";

		m_cube_shader.reset(JEngine::Shader::Create(vertshader, fragshader));
		
		std::shared_ptr<JEngine::VertexBuffer> vertexbuffer;
		std::shared_ptr<JEngine::IndexBuffer> indexbuffer;

		JEngine::ShapeData cube = JEngine::ShapeGenerator::makeCube();

		vertexbuffer.reset(JEngine::VertexBuffer::Create(cube));
		vertexbuffer->SetLayout({
				{"Position", JEngine::ShaderDataType::Float3},
				{"Color", JEngine::ShaderDataType::Float3},
				{"Normal", JEngine::ShaderDataType::Float3}
			});

		indexbuffer.reset(JEngine::IndexBuffer::Create(cube));

		m_cube_VertexArray.reset(JEngine::VertexArray::Create());
		m_cube_VertexArray->AddVertexBuffer(vertexbuffer);
		m_cube_VertexArray->AddIndexBuffer(indexbuffer);
		cube.CleanUp();
	}

private:
		std::shared_ptr<JEngine::VertexArray> m_cube_VertexArray;
		std::shared_ptr<JEngine::Shader> m_cube_shader;
		JEngine::ProjectiveCameraController m_CameraController;
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

