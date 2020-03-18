#pragma once

#include "JEngine/Layer.h"

#include "JEngine/Events/ApplicationEvent.h"
#include "JEngine/Events/KeyEvent.h"
#include "JEngine/Events/MouseEvent.h"
#include "JEngine/Events/Event.h"

namespace JEngine {
	
	class JE_API ImGuiLayer : public Layer{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time;
	};
}