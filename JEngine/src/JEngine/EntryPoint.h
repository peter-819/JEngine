#pragma once

#ifdef JE_PLATFORM_WINDOWS

extern JEngine::Application* JEngine::createApplication();
extern std::string JEngine::J_ClassName;
extern HINSTANCE JEngine::J_hInstance;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	JEngine::J_hInstance = hInstance;
	JEngine::J_ClassName = "JEngine";

	JEngine::Log::Init();
	JE_CORE_WARN("Initialized Log!");
	auto p = JEngine::createApplication();
	p->AppRun();
	delete p;
	return 0;
}

#endif