# Add defines
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_BUILD_DLL)
add_compile_definitions(AX_ENABLE_ASSERTS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set rules for glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Set rules for bgfx
set(BGFX_AMALGAMATED OFF CACHE BOOL "" FORCE)
set(BX_AMALGAMATED OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_EXAMPLES ON CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS_BIN2C OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS_GEOMETRY OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS_SHADER OFF CACHE BOOL "" FORCE)
set(BGFX_BUILD_TOOLS_TEXTURE OFF CACHE BOOL "" FORCE)
set(BGFX_CONFIG_MULTITHREADED OFF CACHE BOOL "" FORCE) # TEMPORARY change this later
set(BGFX_INSTALL OFF CACHE BOOL "" FORCE)

# Add subdirectories
add_subdirectory(External/glfw)
add_subdirectory(External/bgfx)
add_subdirectory(External/entt)

# Third party includes
include_directories(External/spdlog/include)
include_directories(External/GLFW/include)
include_directories(External/imgui)
include_directories(External/glm)
include_directories(External/entt/src)
include_directories(External/entt/src)
include_directories(External/bgf/bgfx.cmake/bx/include)
include_directories(External/bgf/bgfx.cmake/bimg/include)
include_directories(External/bgf/bgfx.cmake/bgfx/include)

# Self include directories
include_directories(Source)

# TODO: lets not manually include all cpp files xd
# Create a static library
add_library(Engine STATIC
  # Core
  Source/Core/Application.cpp
  Source/Core/Log.cpp
  Source/Core/Layer.cpp
  Source/Core/LayerStack.cpp

  # Scene
  Source/Scene/Scene.cpp
  Source/Scene/Entity.cpp

  # Rendering
  Source/Renderer/Renderer.cpp
  Source/Renderer/Shader.cpp
  Source/Renderer/Buffer.cpp
  Source/Renderer/VertexArray.cpp
  Source/Renderer/Texture.cpp
  Source/Renderer/RendererAPI.cpp
  Source/Renderer/RenderCommand.cpp
  Source/Renderer/Camera.cpp
  Source/Renderer/CameraController.cpp
  
  Source/Platform/OpenGL/OpenGLContext.cpp
  Source/Platform/OpenGL/OpenGLBuffer.cpp
  Source/Platform/OpenGL/OpenGLVertexArray.cpp
  Source/Platform/OpenGL/OpenGLRendererAPI.cpp

  # Imgui
  Source/ImGui/ImGuiLayer.cpp
  Source/ImGui/ImGuiBuild.cpp

  # Windows
  Source/Platform/Windows/WindowsWindow.cpp
  Source/Platform/Windows/WindowsInput.cpp
)

# Link up
target_link_libraries(Engine PRIVATE gflw bgfx bx)

# PCH
target_precompile_headers(Engine PRIVATE Source/axpch.hpp)