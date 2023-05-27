# Add defines
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_BUILD_DLL)
add_compile_definitions(AX_ENABLE_ASSERTS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set rules for sdl

# Set rules for bgfx

# Add subdirectories
add_subdirectory(External/SDL)
add_subdirectory(External/bgfx)
add_subdirectory(External/entt)

# Third party includes
include_directories(External/spdlog/include)
include_directories(External/GLFW/include)
include_directories(External/Glad/include)
include_directories(External/imgui)
include_directories(External/glm)
include_directories(External/entt/src)

# Self include directories
# include_directories(Source)

# TODO: lets not manually include all cpp files xd
# Create a static library
add_library(Engine STATIC
  # Core
  Source/Apex/Application.cpp
  Source/Apex/Log.cpp
  Source/Apex/Layer.cpp
  Source/Apex/LayerStack.cpp

  # Scene
  Source/Apex/Scene/Scene.cpp
  Source/Apex/Scene/Entity.cpp

  # Rendering
  Source/Apex/Renderer/Renderer.cpp
  Source/Apex/Renderer/Shader.cpp
  Source/Apex/Renderer/Buffer.cpp
  Source/Apex/Renderer/VertexArray.cpp
  Source/Apex/Renderer/Texture.cpp
  Source/Apex/Renderer/RendererAPI.cpp
  Source/Apex/Renderer/RenderCommand.cpp
  Source/Apex/Renderer/PerspectiveCamera.cpp
  Source/Apex/Renderer/PerspectiveCameraController.cpp
  
  Source/Platform/OpenGL/OpenGLContext.cpp
  Source/Platform/OpenGL/OpenGLBuffer.cpp
  Source/Platform/OpenGL/OpenGLVertexArray.cpp
  Source/Platform/OpenGL/OpenGLRendererAPI.cpp

  # Imgui
  Source/Apex/ImGui/ImGuiLayer.cpp
  Source/Apex/ImGui/ImGuiBuild.cpp

  # Windows
  Source/Platform/Windows/WindowsWindow.cpp
  Source/Platform/Windows/WindowsInput.cpp
)

# Link up
target_link_libraries(Engine PRIVATE glfw glad opengl32)

# PCH
target_precompile_headers(Engine PRIVATE Source/axpch.hpp)