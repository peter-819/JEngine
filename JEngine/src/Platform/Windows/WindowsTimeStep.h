#include "JEngine/Core/TimeStep.h"
#include <Windows.h>

namespace JEngine {
	class WindowsTimeStep : public TimeStep {
	public:
		virtual void GetNewFrame() override;
		virtual void Init() override;
		
	private:
		LARGE_INTEGER LastFrameCounter;
		LARGE_INTEGER DeltaCounter;
		LARGE_INTEGER PerformanceFrequency;
	};
}