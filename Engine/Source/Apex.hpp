#pragma once

// Used by editor and runtime
#include "Core/Application.hpp"
#include "Core/Layer.hpp"
#include "Core/Log.hpp"

#include "Core/Timestep.hpp"

#include "Renderer/Renderer.hpp"
#include "Renderer/RenderCommand.hpp"

#include "Renderer/Buffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"

#include "Renderer/Camera.hpp"

#include "Scene/Scene.hpp"
#include "Scene/Entity.hpp"
#include "Scene/Components.hpp"

#include "Input.hpp"
#include "KeyCodes.hpp"
#include "MouseButtonCodes.hpp"

// Events TEMPORARY
#include "Events/ApplicationEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"

#include "ImGui/ImGuiLayer.hpp"

// Entry point
#include "Core/EntryPoint.hpp"