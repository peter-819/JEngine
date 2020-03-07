//#include "Application.h"

extern JEngine::Application* JEngine::createApplication();

int main() {
	auto p = JEngine::createApplication();
	p->run();
	delete p;
	return 0;
}