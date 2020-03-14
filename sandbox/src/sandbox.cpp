#include <JEngine.h>
#include <cstdio>

class ExampleLayer : public JEngine::Layer {
public:
	ExampleLayer() :Layer("Example"){}

	void OnAttach() override {
		glTriangleTest();
	}

	void OnUpdate() override {
		
		JEngine::RenderCommand::Clear();
		JEngine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1.0f });

		JEngine::ProjectiveCamera camera;
		camera.SetProjection(60.0f, 1200.0f / 720.0f, 0.1f, 20.0f);
		JEngine::Renderer::BeginScene(camera);
		//JEngine::Renderer::Submit(m_sq_VertexArray);
		JEngine::Renderer::Submit(m_cube_shader,m_cube_VertexArray);
		JEngine::Renderer::EndScene();
	}

	void OnEvent(JEngine::Event& event) override {

	}

	void glTriangleTest() {
		
		/*std::string vertshader = R"(
		#version 430
		
		in layout(location = 0) vec2 position;

		uniform vec3 InColor;

		out vec3 theColor;

		void main() {
			vec4 v = vec4(position.x, position.y, 0.0, 1.0);
			gl_Position = v;
			theColor = InColor;
		})";

		std::string fragshader = R"(
		#version 430

		in vec3 theColor;
		
		out vec4 daColor;

		void main(){
			daColor = vec4(theColor,1.0);	
		}
		
		)";*/

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

		/*float sqverts[] = {
			-0.7f, -0.7f,
			-0.7f, +0.7f,
			+0.7f, +0.7f,
			+0.7f, -0.7f,
		};
		uint32_t sqind[] = { 0,1,2,2,3,0 };

		vertexbuffer.reset(JEngine::VertexBuffer::Create(sqverts, sizeof sqverts));
		vertexbuffer->SetLayout({
				{ "Postion",JEngine::ShaderDataType::Float2 }
			});

		indexbuffer.reset(JEngine::IndexBuffer::Create(sqind, 6));

		m_sq_VertexArray.reset(JEngine::VertexArray::Create());
		m_sq_VertexArray->AddVertexBuffer(vertexbuffer);
		m_sq_VertexArray->AddIndexBuffer(indexbuffer);*/
		cube.CleanUp();
	}

private:
		std::shared_ptr<JEngine::VertexArray> m_cube_VertexArray;
		//std::shared_ptr<JEngine::VertexArray> m_sq_VertexArray;
		std::shared_ptr<JEngine::Shader> m_cube_shader;
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

