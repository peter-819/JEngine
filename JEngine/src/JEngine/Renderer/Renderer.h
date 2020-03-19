#pragma once
#include "JEpch.h"
#include "RendererAPI.h"
#include "JEngine/Renderer/VertexArray.h"
#include "Shader.h"
#include "Camera/ProjectiveCamera.h"
#include "Light/Light.h"
#include "glm.hpp"

namespace JEngine {

	class Renderer {
		public:
			static RendererAPI::API GetAPI() { return m_API; }
		
			static void BeginScene(const ProjectiveCamera& camera,const Light& light);
			static void BeginScene(const ProjectiveCamera& camera);
			static void EndScene();

			static void Submit(
				const Ref<Shader>& shader,
				const Ref<VertexArray>& vertexarray,
				const glm::mat4& Transform
			);
			static void OnWindowResize(uint32_t width,uint32_t height);

		private:

			struct SceneData {
				ProjectiveCamera camera;
				std::vector<Light> lights;
			};
			
			static Scope<SceneData> m_SceneData;
			static RendererAPI::API m_API;
	};
}