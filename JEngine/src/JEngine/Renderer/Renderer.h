#pragma once
#include "JEpch.h"
#include "RendererAPI.h"
#include "JEngine/Renderer/VertexArray.h"
namespace JEngine {

	class Renderer {
		public:
			static RendererAPI::API GetAPI() { return m_API; }
		
			static void BeginScene();
			static void EndScene();

			static void Submit(const std::shared_ptr<VertexArray>& vertexarray);

		private:
			static RendererAPI::API m_API;
	};
}