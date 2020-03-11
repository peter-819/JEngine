#include <JEngine.h>
#include <cstdio>

class ExampleLayer : public JEngine::Layer {
public:
	ExampleLayer() :Layer("Example"){}

	void OnUpdate()override {
		//JE_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(JEngine::Event& event) override {

		if (event.GetEventType() == JEngine::EventType::KeyPressed) {
			JEngine::KeyPressedEvent &e = (JEngine::KeyPressedEvent&)event;
			
			if (JEngine::Input::IsKeyPressed(JE_KEY_LEFT_SHIFT))
				JE_CLIENT_TRACE("left shift pressed !");
			JE_CLIENT_TRACE("??? {0}, {1}", (char)e.GetKeyCode(),e.GetRepeatCount());
		}
		//JE_CLIENT_TRACE("{0}", event);
	}
};

class sandbox : public JEngine::Application {
public:
	sandbox(){
		PushLayer(new ExampleLayer());
	}
	~sandbox(){}
	virtual void run()override{

	}
};

JEngine::Application* JEngine::createApplication() {
	return new sandbox();
}

