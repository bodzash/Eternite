#If windows
add_compile_definitions(AX_PLATFORM_WINDOWS)
add_compile_definitions(AX_BUILD_DLL)

include_directories(${PROJECT_SOURCE_DIR}/Engine/External/spdlog/include)

include_directories(${PROJECT_SOURCE_DIR}/Engine/Source)
add_library(Engine SHARED
  Source/Apex/Application.cpp
  Source/Apex/Log.cpp
)