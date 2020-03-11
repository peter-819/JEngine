#pragma once
#include "JEpch.h"

namespace JEngine {
	
	class GraphicContext {
	
	public:
		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}