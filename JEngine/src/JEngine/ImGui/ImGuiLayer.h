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

		void OnAttach();
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);

		bool OnMouseButtonPressed(MouseButtonPressedEvent &e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnKeyTyped(KeyTypedEvent& e);

		bool OnWindowResize(WindowResizeEvent& e);

	private:
		float m_Time;
	};
}
//
//WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
//AppTick, AppUpdate, AppRender,
//KeyPressed, KeyReleased,
//MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled