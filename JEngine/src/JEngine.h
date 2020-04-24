#pragma once

//----------JEngine Side-------------//
#include "JEngine/Application.h"
#include "JEngine/Core/Log.h"
#include "JEngine/Core/Input.h"
#include "JEngine/Core/Layer.h"

#include "JEngine/Events/KeyEvent.h"
#include "JEngine/Events/MouseEvent.h"
#include "JEngine/Events/ApplicationEvent.h"
#include "JEngine/Events/Event.h"
#include "JEngine/Events/keycode.h"


#include "JEngine/ImGui/ImGuiLayer.h"

#include "JEngine/Renderer/Buffer.h"
#include "JEngine/Renderer/BufferLayout.h"
#include "JEngine/Renderer/GraphicContext.h"
#include "JEngine/Renderer/RenderCommand.h"
#include "JEngine/Renderer/Renderer.h"
#include "JEngine/Renderer/RendererAPI.h"
#include "JEngine/Renderer/VertexArray.h"
#include "JEngine/Renderer/Shader.h"
#include "JEngine/Renderer/Camera/ProjectiveCamera.h"
#include "JEngine/Renderer/Camera/ProjectiveCameraController.h"
#include "JEngine/Renderer/Light/Light.h"

#include "JEngine/Shape/Mesh.h"
#include "JEngine/Shape/MeshGenerator.h"

#include "JEngine/Core/TimeStep.h"

//-----------Client Side-------------//
//--- TODO: Remove these includes ---//
#include "gtx/transform.hpp"
#include "glm.hpp"

#include "imgui.h"