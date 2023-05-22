#If windows
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_BUILD_DLL)
add_compile_definitions(AX_ENABLE_ASSERTS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(External/GLFW)

# Very cursed workaround
add_compile_definitions(GLFW_INCLUDE_NONE)

add_subdirectory(External/Glad)
#add_subdirectory(External/imgui)

include_directories(External/spdlog/include)
include_directories(External/GLFW/include)
include_directories(External/Glad/include)
include_directories(External/imgui)
include_directories(External/glm)

# Self
include_directories(Source)

# TODO: lets not manually include all cpp files xd
add_library(Engine STATIC
  # Engine
  Source/Apex/Application.cpp
  Source/Apex/Log.cpp
  Source/Apex/Layer.cpp
  Source/Apex/LayerStack.cpp

  # Imgui
  Source/Apex/ImGui/ImGuiLayer.cpp
  Source/Apex/ImGui/ImGuiBuild.cpp

  # Windows
  Source/Platform/Windows/WindowsWindow.cpp
  Source/Platform/Windows/WindowsInput.cpp
)

target_link_libraries(Engine PRIVATE glfw glad opengl32)

target_precompile_headers(Engine PRIVATE Source/axpch.hpp)