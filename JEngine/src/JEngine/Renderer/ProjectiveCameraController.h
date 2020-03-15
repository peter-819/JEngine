#pragma once

#include "ProjectiveCamera.h"
#include "JEngine/Events/MouseEvent.h"

namespace JEngine {
	class ProjectiveCameraController {
	public:
		ProjectiveCameraController() :m_Camera(), m_MousePosition({-1.0f,-1.0f}) {}
		ProjectiveCameraController(const ProjectiveCamera& camera) :m_Camera(camera) {}
		void OnUpdate(float ts);
		void OnEvent(Event& e);

		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseScrolled(MouseScrolledEvent& e);
		const ProjectiveCamera& GetCamera() const { return m_Camera; }
	private:
		ProjectiveCamera m_Camera;
		std::pair<float, float> m_MousePosition;
	};
}