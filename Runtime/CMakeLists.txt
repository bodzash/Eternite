# If windows
add_compile_definitions(EN_PLATFORM_WINDOWS)

include_directories(${PROJECT_SOURCE_DIR}/Engine/Source)
include_directories(${PROJECT_SOURCE_DIR}/Runtime/Source)

link_directories(${PROJECT_SOURCE_DIR}/Engine/Source)
add_executable(Runtime Source/Runtime.cpp)
target_link_libraries(Runtime Engine)