#pragma once

namespace JEngine {
	class TimeStep {
	public:
		virtual void GetNewFrame() = 0;
		virtual void Init() = 0;

		static TimeStep* Create();
		float GetDeltaTime() const { return m_DeltaTime; }
	protected:
		float m_DeltaTime;
	};
}