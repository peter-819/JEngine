#include "JEpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace JEngine {
	RendererAPI* RenderCommand::m_Api = new OpenGLRendererAPI;
}