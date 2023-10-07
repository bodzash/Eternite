# Add defines
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_ENABLE_ASSERTS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set rules for raylib
set(OPENGL_VERSION 2.1)

# Add subdirectories (modules with cmake file)
add_subdirectory(External/raylib)

# TODO: lets not manually include all cpp files xd
# Create a static library
add_library(Engine STATIC
	# Core
	Source/Core/Application.cpp
	Source/Core/Log.cpp
	Source/Core/Layer.cpp
	Source/Core/LayerStack.cpp
	Source/Core/Window.cpp
	Source/Core/Input.cpp

	# Scene
	Source/Scene/Scene.cpp
	Source/Scene/Entity.cpp

	# Rendering
	Source/Renderer/Renderer.cpp
	Source/Renderer/Shader.cpp
	Source/Renderer/VertexArray.cpp
	Source/Renderer/Texture.cpp
	Source/Renderer/RendererAPI.cpp
	Source/Renderer/RenderCommand.cpp
	Source/Renderer/Camera.cpp
	Source/Renderer/CameraController.cpp
	Source/Renderer/GraphicsContext.cpp

	# Imgui
	Source/ImGui/ImGuiLayer.cpp
	Source/ImGui/ImGuiBuild.cpp
)

# Third party includes
target_include_directories(Engine PUBLIC External/spdlog/include)
target_include_directories(Engine PUBLIC External/imgui)
target_include_directories(Engine PUBLIC External/glm)
target_include_directories(Engine PUBLIC External/entt/src)
target_include_directories(Engine PUBLIC External/raylib/src)

# Self include directories
# target_include_directories(Engine PUBLIC Source)

# Link up
target_link_libraries(Engine PRIVATE raylib)

# PCH
target_precompile_headers(Engine PRIVATE Source/axpch.h)