#pragma once
#include "core.h"
namespace JEngine {
	class JE_API Application
	{
	public:
		void run();
		Application();
		virtual ~Application();
	};
	Application* createApplication();
}
