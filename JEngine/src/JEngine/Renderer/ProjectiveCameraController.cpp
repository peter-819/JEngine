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
			delta += m_Camera.m_UP * speed;

		if (Input::IsKeyPressed(JE_KEY_SPACE))
			delta -= m_Camera.m_UP * speed;

		m_Camera.m_Position += delta;
	}

	void ProjectiveCameraController::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseMovedEvent>(JE_BIND_EVENT_FN(ProjectiveCameraController::OnMouseMoved));
	}

	bool ProjectiveCameraController::OnMouseMoved(MouseMovedEvent& e) {
		auto[x,y] = Input::GetMousePos();
		glm::vec2 MouseDelta = glm::vec2(x - e.GetX(), y - e.GetY());

		m_Camera.m_ViewDirection = glm::mat3(glm::rotate(-MouseDelta.x * 0.0015f, m_Camera.m_UP)) * m_Camera.m_ViewDirection;
		m_Camera.m_ViewDirection = glm::mat3(glm::rotate(MouseDelta.y * 0.003f, glm::cross(m_Camera.m_UP, m_Camera.m_ViewDirection))) * m_Camera.m_ViewDirection;
		return false;

		Compile error
		//TODO : NOT WORK
	}
}