#include <JEngine.h>
#include <cstdio>

class sandbox : public JEngine::Application {
public:
	sandbox(){}
	~sandbox(){}
};

JEngine::Application* JEngine::createApplication() {
	return new sandbox();
}

