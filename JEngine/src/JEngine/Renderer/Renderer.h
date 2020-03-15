#pragma once
#include "JEpch.h"
#include "RendererAPI.h"
#include "JEngine/Renderer/VertexArray.h"
#include "Shader.h"
#include "ProjectiveCamera.h"
#include "Light.h"
#include "glm.hpp"

namespace JEngine {

	class Renderer {
		public:
			static RendererAPI::API GetAPI() { return m_API; }
		
			static void BeginScene(const ProjectiveCamera& camera,const Light& light);
			static void EndScene();

			static void Submit(
				const Ref<Shader>& shader,
				const Ref<VertexArray>& vertexarray,
				const glm::mat4& Transform
			);
			static void OnWindowResize(uint32_t width,uint32_t height);

		private:

			struct SceneData {
				glm::mat4 viewProjection;
				glm::vec3 CameraPosition;
				
				glm::vec3 LightPosition;
				float AmbientLightScalar;
				float DiffuseLightScalar;
				float SpecularLightRadius;
				float SpecularLightPow;

			};
			
			static Scope<SceneData> m_SceneData;
			static RendererAPI::API m_API;
	};
}