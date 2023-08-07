# Add defines
add_compile_definitions(AX_PLATFORM_WINDOWS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create executable
add_executable(Runtime Source/Runtime.cpp ../Content/Metadata/Favicon.ico)

# Third party
target_include_directories(Runtime PRIVATE Engine/External/spdlog/include)
target_include_directories(Runtime PRIVATE Engine/External/imgui)
target_include_directories(Runtime PRIVATE Engine/External/entt/src)
target_include_directories(Runtime PRIVATE Engine/External/glm/glm)

# Self include directories
#target_include_directories(Runtime PRIVATE Engine/Source)
#target_include_directories(Runtime PRIVATE Runtime/Source)

# Link library
target_link_directories(Runtime PUBLIC Engine/Source)

# Link up
target_link_libraries(Runtime PRIVATE Engine)