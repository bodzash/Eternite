#If windows
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_BUILD_DLL)
add_compile_definitions(AX_ENABLE_ASSERTS)

add_subdirectory(External/GLFW)

# Very cursed workaround
add_compile_definitions(GLFW_INCLUDE_NONE)

add_subdirectory(External/Glad)

# Library inlcude
#include_directories(${PROJECT_SOURCE_DIR}/Engine/External/spdlog/include)
#include_directories(${PROJECT_SOURCE_DIR}/Engine/External/GLFW/include)
#include_directories(${PROJECT_SOURCE_DIR}/Engine/External/Glad/include)

include_directories(External/spdlog/include)
include_directories(External/GLFW/include)
include_directories(External/Glad/include)

# Self
include_directories(Source)
#include_directories(${PROJECT_SOURCE_DIR}/Engine/Source)

# TODO: lets not manually include all cpp files xd
add_library(Engine SHARED
  Source/Apex/Application.cpp
  Source/Apex/Log.cpp
  Source/Apex/Layer.cpp
  Source/Apex/LayerStack.cpp
  Source/Platform/Windows/WindowsWindow.cpp
)

target_link_libraries(Engine PRIVATE glfw glad)

#target_precompile_headers(Engine PRIVATE ${PROJECT_SOURCE_DIR}/Engine/Source/axpch.hpp)
target_precompile_headers(Engine PRIVATE Source/axpch.hpp)