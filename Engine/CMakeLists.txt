# Add defines
add_compile_definitions(AX_ENABLE_ASSERTS)
#add_compile_definitions(AX_HEADLESS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set rules for RAYLIB
set(OPENGL_VERSION 2.1)

# Set rules for BOX2D
set(BOX2D_BUILD_UNIT_TESTS OFF)
set(BOX2D_BUILD_TESTBED OFF)
set(BOX2D_BUILD_DOCS OFF)
set(BOX2D_USER_SETTINGS OFF)

# Add subdirectories
add_subdirectory(External/raylib)
add_subdirectory(External/box2d)

set(BOX2D_USER_SETTINGS OFF)

# Create as a static library
add_library(Engine STATIC
	# Core
	Source/Core/Application.cpp
	Source/Core/HeadlessApplication.cpp
	Source/Core/Log.cpp
	Source/Core/Layer.cpp
	Source/Core/LayerStack.cpp
	Source/Core/Window.cpp
	Source/Core/Input.cpp

	# Scene
	Source/Scene/Scene.cpp
	Source/Scene/Entity.cpp
	Source/Scene/Components.cpp

	# Rendering
	Source/Renderer/Camera.cpp
	Source/Renderer/CameraController.cpp
	Source/Renderer/Renderer.cpp

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
target_include_directories(Engine PUBLIC External/box2d/include)

# Self include directories
target_include_directories(Engine PUBLIC Source)

# Link libraries
target_link_libraries(Engine PRIVATE raylib box2d)

# PCH
target_precompile_headers(Engine PRIVATE Source/axpch.h)