#pragma once
#include "JEpch.h"
#include "JEngine/Core/Window.h"
namespace JEngine {
	extern WINDOWAPI WindowAPI;
	class GraphicContext {
	
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}