#pragma once

#include "ProjectiveCamera.h"
#include "JEngine/Events/MouseEvent.h"

namespace JEngine {
	class ProjectiveCameraController {
	public:
		ProjectiveCameraController():m_Camera(){
		}
		ProjectiveCameraController(const ProjectiveCamera& camera) :m_Camera(camera) {}
		void OnUpdate(float ts);
		void OnEvent(Event& e);

		bool OnMouseMoved(MouseMovedEvent& e);
		const ProjectiveCamera& GetCamera() const { return m_Camera; }
	private:
		ProjectiveCamera m_Camera;
	};
}