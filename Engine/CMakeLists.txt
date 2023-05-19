#If windows
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_BUILD_DLL)

# Libraries
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/spdlog/include)

# Self
include_directories(${PROJECT_SOURCE_DIR}/Engine/Source)

add_library(Engine SHARED
  Source/Apex/Application.cpp
  Source/Apex/Log.cpp
)

target_precompile_headers(Engine PRIVATE ${PROJECT_SOURCE_DIR}/Engine/Source/axpch.hpp)