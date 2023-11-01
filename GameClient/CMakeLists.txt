# Add defines

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create executable
add_executable(Client
    # ../Data/Metadata/Metadata.rc

    # Core
    Source/Client.cpp

    # TEMPORARY
    Source/Utils/Utils.cpp
)

# Third party
target_include_directories(Client PRIVATE Engine/External/spdlog/include)
target_include_directories(Client PRIVATE Engine/External/imgui)
target_include_directories(Client PRIVATE Engine/External/entt/src)
target_include_directories(Client PRIVATE Engine/External/glm/glm)

# Self include directories
#target_include_directories(Client PRIVATE Engine/Source)
#target_include_directories(Client PRIVATE Client/Source)

# Link libraries
target_link_directories(Client PUBLIC Engine/Source)

# Link up
target_link_libraries(Client PRIVATE Engine)