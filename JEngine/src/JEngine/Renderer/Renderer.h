#pragma once
#include "JEpch.h"
#include "RendererAPI.h"
#include "JEngine/Renderer/VertexArray.h"
#include "Shader.h"
#include "ProjectiveCamera.h"
#include "glm.hpp"

namespace JEngine {

	class Renderer {
		public:
			static RendererAPI::API GetAPI() { return m_API; }
		
			static void BeginScene(const ProjectiveCamera& camera);
			static void EndScene();

			static void Submit(
				const std::shared_ptr<Shader>& shader,
				const std::shared_ptr<VertexArray>& vertexarray
			);
			static void OnWindowResize(uint32_t width,uint32_t height);

		private:

			struct SceneData {
				glm::mat4 viewProjection;
			};
			
			static std::unique_ptr<SceneData> m_SceneData;
			static RendererAPI::API m_API;
	};
}