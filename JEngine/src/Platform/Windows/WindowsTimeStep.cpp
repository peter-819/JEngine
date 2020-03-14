#include "JEpch.h"
#include "WindowsTimeStep.h"

namespace JEngine {
	void WindowsTimeStep::Init() {
		bool errorCode = QueryPerformanceFrequency(&PerformanceFrequency);
		JE_CORE_ASSERT(errorCode, "Can't Query Performace Frequency !");
		m_DeltaTime = 0;
		LastFrameCounter.QuadPart = 0;
	}

	void WindowsTimeStep::GetNewFrame() {
		LARGE_INTEGER nowFrameCounter;
		bool errorCode = QueryPerformanceCounter(&nowFrameCounter);
		JE_CORE_ASSERT(errorCode,"Can't Query Performace Counter !")
		DeltaCounter.QuadPart = nowFrameCounter.QuadPart - LastFrameCounter.QuadPart;
		if (LastFrameCounter.QuadPart != 0)
			m_DeltaTime = ((float)DeltaCounter.QuadPart) / PerformanceFrequency.QuadPart;
		LastFrameCounter.QuadPart = nowFrameCounter.QuadPart;
	}
}