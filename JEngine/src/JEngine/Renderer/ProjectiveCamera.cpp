#include "JEpch.h"
#include "ProjectiveCamera.h"
namespace JEngine {
	ProjectiveCamera::ProjectiveCamera() {
		m_Position = glm::vec3(-10.0f, -10.0f, 10.0f);
		m_ViewDirection = glm::normalize(glm::vec3(10.0f, 10.0f, -10.0f));
		m_UP = glm::vec3(0.0f, 1.0f, 0.0f);

		m_ViewAngle = 60.0f;
		m_Aspect = 1200.0f / 720.0f;
		m_Znear = 0.1f;
		m_Zfar = 20.0f;
	}
}