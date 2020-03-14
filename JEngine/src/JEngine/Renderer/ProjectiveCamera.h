#pragma once
#include "glm.hpp"
#include "gtx/transform.hpp"
namespace JEngine {
	class ProjectiveCamera {
		friend class ProjectiveCameraController;
	public:
		ProjectiveCamera();
		~ProjectiveCamera() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		const glm::vec3& GetViewDirction() const { return m_ViewDirection; }
		const glm::vec3& GetUP() const { return m_UP; };
		
		const glm::mat4& GetMatrix() const {
			glm::mat4 Pmat = glm::perspective(glm::radians(m_ViewAngle), m_Aspect, m_Znear, m_Zfar);
			glm::mat4 Cmat = glm::lookAt(m_Position, m_Position + m_ViewDirection, m_UP);
			return Pmat * Cmat;
		}
		const glm::mat4& GetCameraMatrix() const { 
			return glm::lookAt(m_Position, m_Position + m_ViewDirection, m_UP);
		}
		const glm::mat4& GetProjectMatrix() const {
			return glm::perspective(glm::radians(m_ViewAngle), m_Aspect, m_Znear, m_Zfar);
		}

		void SetPosition(const glm::vec3& position) { m_Position = position; }
		void SetViewDirection(const glm::vec3& viewdirection) { m_ViewDirection = viewdirection;  }
		void SetUP(const glm::vec3& up) { m_UP = up;}

		void SetProjection(float viewangle, float aspect, float znear, float zfar) {
			m_ViewAngle = viewangle;
			m_Aspect = aspect;
			m_Znear = znear;
			m_Zfar = zfar;
		}

	private:
		//void CalcMatrix();
	private:
		glm::vec3 m_Position;
		glm::vec3 m_ViewDirection;
		glm::vec3 m_UP;

		float m_ViewAngle;
		float m_Aspect;
		float m_Znear;
		float m_Zfar;
	//private:
	//	glm::mat4 m_ProjectMatrix;
	//	glm::mat4 m_CameraMatrix;
	//	glm::mat4 m_FullMatrix;
	};
}