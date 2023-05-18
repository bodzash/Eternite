# If windows
add_compile_definitions(EN_PLATFORM_WINDOWS)
add_compile_definitions(EN_BUILD_DLL)

include_directories(${PROJECT_SOURCE_DIR}/Engine/Source)
add_library(Engine SHARED Source/Engine/Application.cpp)