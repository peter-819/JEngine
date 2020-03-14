#pragma once
#include "glm.hpp"
#include "gtx/transform.hpp"
namespace JEngine {
	class ProjectiveCamera {
	public:
		ProjectiveCamera();
		~ProjectiveCamera() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetViewDirction() const { return m_ViewDirection; }
		const glm::vec3& GetUP() const { return m_UP; };
		
		const glm::mat4& GetMatrix() const { return m_FullMatrix; }
		const glm::mat4& GetCameraMatrix() const { return m_CameraMatrix; }
		const glm::mat4& GetProjectMatrix() const { return m_ProjectMatrix; }

		void SetPosition(const glm::vec3& position) { m_Position = position; CalcMatrix(); }
		void SetViewDirection(const glm::vec3& viewdirection) { m_ViewDirection = viewdirection; CalcMatrix(); }
		void SetUP(const glm::vec3& up) { m_UP = up; CalcMatrix();}

		void SetProjection(float viewangle, float aspect, float znear, float zfar) {
			m_ProjectMatrix = glm::perspective(glm::radians(viewangle), aspect, znear, zfar);
			CalcMatrix();
		}

	private:
		void CalcMatrix();
	private:
		glm::vec3 m_Position;
		glm::vec3 m_ViewDirection;
		glm::vec3 m_UP;
	private:
		glm::mat4 m_ProjectMatrix;
		glm::mat4 m_CameraMatrix;
		glm::mat4 m_FullMatrix;
	};
}