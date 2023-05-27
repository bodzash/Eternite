# Add defines
add_compile_definitions(AX_PLATFORM_WINDOWS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Third party
include_directories(Engine/External/spdlog/include)
include_directories(Engine/External/imgui)
include_directories(Engine/External/entt/src)
include_directories(Engine/External/glm/glm)

# Self include directories
include_directories(Engine/Source)
include_directories(Runtime/Source)

# Link library
link_directories(Engine/Source)

# Create executable
add_executable(Runtime Source/Runtime.cpp)

# Link up
target_link_libraries(Runtime Engine)