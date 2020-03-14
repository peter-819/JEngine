#include "JEpch.h"
#include "TimeStep.h"
#include "JEngine/Renderer/Renderer.h"
#include "Platform/Windows/WindowsTimeStep.h"

namespace JEngine {
	TimeStep* TimeStep::Create() {
#ifdef JE_PLATFORM_WINDOWS
	return new WindowsTimeStep();
#else 
	return nullptr;
#endif
	}
}
