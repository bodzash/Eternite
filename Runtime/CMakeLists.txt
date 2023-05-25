# If windows
add_compile_definitions(AX_PLATFORM_WINDOWS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Third party
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/include)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/imgui)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/entt/src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm)

# Own
include_directories(${PROJECT_SOURCE_DIR}/Engine/Source)
include_directories(${PROJECT_SOURCE_DIR}/Runtime/Source)

link_directories(${PROJECT_SOURCE_DIR}/Engine/Source)
add_executable(Runtime Source/Runtime.cpp)
target_link_libraries(Runtime Engine)