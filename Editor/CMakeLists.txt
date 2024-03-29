# Add defines

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Conditional soure files
set(PLATFORM_SRC)

# Platform check for source files
if (WIN32)
    set(PLATFORM_SRC ${PLATFORM_SRC} Source/FileDialog/FileDialogWindows.cpp)
endif()

# Create executable
add_executable(Editor
    # Core
    Source/Editor.cpp
    Source/EditorLayer.cpp

    # Panels
    Source/Panels/HierarchyPanel.cpp

    # Platform specific
    ${PLATFORM_SRC}
)

# Third party
target_include_directories(Editor PRIVATE Engine/External/spdlog/include)
target_include_directories(Editor PRIVATE Engine/External/imgui)
target_include_directories(Editor PRIVATE Engine/External/entt/src)
target_include_directories(Editor PRIVATE Engine/External/glm/glm)
# maybe raylib here

# Link libraries
target_link_directories(Editor PUBLIC Engine/Source)

# Link up
target_link_libraries(Editor PRIVATE Engine)