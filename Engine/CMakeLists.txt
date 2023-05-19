#If windows
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_BUILD_DLL)
add_compile_definitions(AX_ENABLE_ASSERTS)


add_subdirectory(External/GLFW)	

# Library inlcude
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/GLFW/include)

# Self
include_directories(${PROJECT_SOURCE_DIR}/Engine/Source)

add_library(Engine SHARED
  Source/Apex/Application.cpp
  Source/Apex/Log.cpp
  Source/Platform/Windows/WindowsWindow.cpp
)

target_link_libraries(Engine PRIVATE glfw)

target_precompile_headers(Engine PRIVATE ${PROJECT_SOURCE_DIR}/Engine/Source/axpch.hpp)