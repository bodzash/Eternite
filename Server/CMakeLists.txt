# Add defines
# add_compile_definitions(AX_HEADLESS)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create executable
add_executable(Server
    # Core
    Source/Server.cpp
)

# Third party
target_include_directories(Server PRIVATE Engine/External/spdlog/include)
target_include_directories(Server PRIVATE Engine/External/imgui)
target_include_directories(Server PRIVATE Engine/External/entt/src)
target_include_directories(Server PRIVATE Engine/External/glm/glm)

# Self include directories
#target_include_directories(Server PRIVATE Engine/Source)
#target_include_directories(Server PRIVATE Server/Source)

# Link libraries
target_link_directories(Server PUBLIC Engine/Source)

# Link up
target_link_libraries(Server PRIVATE Engine)