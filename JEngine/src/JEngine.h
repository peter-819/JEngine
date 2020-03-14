#pragma once

//----------JEngine Side-------------//
#include "JEngine/Application.h"
#include "JEngine/Log.h"

#include "JEngine/Events/KeyEvent.h"
#include "JEngine/Events/MouseEvent.h"
#include "JEngine/Events/ApplicationEvent.h"
#include "JEngine/Events/Event.h"

#include "JEngine/Input.h"
#include "JEngine/Layer.h"

#include "JEngine/keycode.h"
#include "JEngine/ImGui/ImGuiLayer.h"

#include "JEngine/Renderer/Buffer.h"
#include "JEngine/Renderer/BufferLayout.h"
#include "JEngine/Renderer/GraphicContext.h"
#include "JEngine/Renderer/RenderCommand.h"
#include "JEngine/Renderer/Renderer.h"
#include "JEngine/Renderer/RendererAPI.h"
#include "JEngine/Renderer/VertexArray.h"
#include "JEngine/Renderer/Shader.h"
#include "JEngine/Renderer/ProjectiveCamera.h"
#include "JEngine/Renderer/ProjectiveCameraController.h"

#include "JEngine/Shape/ShapeData.h"
#include "JEngine/Shape/ShapeGenerator.h"

#include "JEngine/Core/TimeStep.h"

//-----------Client Side-------------//
#include "JEngine/EntryPoint.h"