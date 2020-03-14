#include "JEpch.h"
#include "ProjectiveCamera.h"
namespace JEngine {
	ProjectiveCamera::ProjectiveCamera() {
		m_Position = glm::vec3(-10.0f, -10.0f, 10.0f);
		m_ViewDirection = glm::vec3(10.0f, 10.0f, -10.0f);
		m_UP = glm::vec3(0.0f, 1.0f, 0.0f);
		CalcMatrix();
	}

	void ProjectiveCamera::CalcMatrix() {
		m_CameraMatrix = glm::lookAt(m_Position, m_Position + m_ViewDirection, m_UP);
		m_FullMatrix = m_ProjectMatrix * m_CameraMatrix;
	}
}