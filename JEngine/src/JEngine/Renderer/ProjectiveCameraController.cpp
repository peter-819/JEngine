#include "JEpch.h"
#include "ProjectiveCameraController.h"
#include "JEngine/Input.h"
#include "JEngine/keycode.h"
#include "gtx/transform.hpp"

namespace JEngine {
	void ProjectiveCameraController::OnUpdate(float ts) {
		glm::vec3 delta(0.0f, 0.0f, 0.0f);

		float speed = 10.0f * ts;
		if (Input::IsKeyPressed(JE_KEY_W))
			delta += m_Camera.m_ViewDirection * speed;

		if (Input::IsKeyPressed(JE_KEY_S))
			delta -= m_Camera.m_ViewDirection * speed;

		if (Input::IsKeyPressed(JE_KEY_A))
			delta -= glm::cross(m_Camera.m_ViewDirection, m_Camera.m_UP) * speed;

		if (Input::IsKeyPressed(JE_KEY_D))
			delta += glm::cross(m_Camera.m_ViewDirection, m_Camera.m_UP) * speed;

		if (Input::IsKeyPressed(JE_KEY_LEFT_SHIFT))
			delta -= m_Camera.m_UP * speed;

		if (Input::IsKeyPressed(JE_KEY_SPACE))
			delta += m_Camera.m_UP * speed;

		m_Camera.m_Position += delta;
	}

	void ProjectiveCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(JE_BIND_EVENT_FN(ProjectiveCameraController::OnMouseMoved));
		dispatcher.Dispatch<MouseScrolledEvent>(JE_BIND_EVENT_FN(ProjectiveCameraController::OnMouseScrolled));
	}

	bool ProjectiveCameraController::OnMouseMoved(MouseMovedEvent& e) {
		auto [x, y] = std::make_pair(e.GetX(), e.GetY());
		glm::vec2 MouseDelta = { 0,0 };

		if (m_MousePosition.first >= 0 && m_MousePosition.second >= 0)
			MouseDelta = glm::vec2(x - m_MousePosition.first, y - m_MousePosition.second);

		if (Input::IsMouseButtonPressed(JE_MOUSE_BUTTON_LEFT)) {
			// Rotate Camera
			if (Input::IsKeyPressed(JE_KEY_LEFT_ALT)) {
				
				m_Camera.m_ViewDirection = glm::mat3(glm::rotate(MouseDelta.x * 0.0015f, m_Camera.m_UP)) * m_Camera.m_ViewDirection;
				m_Camera.m_ViewDirection = glm::mat3(glm::rotate(-MouseDelta.y * 0.003f, glm::cross(m_Camera.m_UP, m_Camera.m_ViewDirection))) * m_Camera.m_ViewDirection;

			}

			m_MousePosition = std::make_pair(x, y);
		}
		// Move Camera
		else if (Input::IsMouseButtonPressed(JE_MOUSE_BUTTON_MIDDLE)) {
			m_Camera.m_Position -= glm::cross(m_Camera.m_ViewDirection, m_Camera.m_UP) * MouseDelta.x * 0.01f;

			m_Camera.m_Position += m_Camera.m_UP * MouseDelta.y * 0.01f;

			m_MousePosition = std::make_pair(x, y);
		}
		else
			m_MousePosition = std::make_pair(-1.0f, -1.0f);

		return false;
	}

	bool ProjectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		float offset = e.GetYOffset();

		m_Camera.m_Position += m_Camera.m_ViewDirection * offset;

		return false;
	}
}