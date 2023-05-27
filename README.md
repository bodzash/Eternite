# Apex Game Engine
A 3D FPS focused game engine

## Notes to self:
Create a Data/AssetLibrary class that holds:
```cpp
    // uint64_t are uuid's (could use strings too i guess)
    std::unordered_map<uint64_t, Mesh> m_Meshes;
    std::unordered_map<uint64_t, Shader> m_Shaders;
    std::unordered_map<uint64_t, Material> m_Materials;
    std::unordered_map<uint64_t, Texture> m_Textures;

    void ImportMesh() {}
```

Implement components in seperate .h and .cpp files and include all of them 
in Components.h

Camera, RigidBody, PointLight, Mesh, Transform, ... and other components

FrameBuffer class

PhysicsWorld, PhysicsMesh class

Folder re-structure: (Will not be nested inside Apex folder)
When these folder become big, use subfolders
Components -> ECS comp.
Core -> Application, Window
Events -> duh
Renderer -> same
Scene -> same
Physics
Scripting -> Native(folder), Lua(folder)
Interface -> ImGui(folder), Noesis(folder)
Navigation (maybe for ai pathfinding)
Audio 


## Architecture
- Engine - This is a lib that the Runtime and Editor can link
- Runtime - This is an Executable that links up with the Engine
- Editor - Level/prefab etc editing tool

## Technologies:
Rendering (only one):
- bgfx *
- Forge (later hopefuly)

Windowing (only one):
- GLFW
- SDL3 *

3D asset importing:
- AssImp * (nice name btw)
- OpenFBX

Logging:
- spdlog *

Benchmarking and Profiling:
- optick *

Entity Component System:
- EnTT * (not even a question)

Scripting (only one):
- C# with Mono
- Lua with Sol3 *
- Native *

Physics (only one):
- Jolt * (most likely because it's aimed at games)

Naviagtion in 3d space (for AI)
- Recast Navigation *

Audio (only one):
- FMOD *
- OpenAL

Game GUI/HUD:
- NoesisGUI *
Note: Blend tool can be used to create these interfaces

Editor/Game debug GUI:
- DearImgui
- Imguizmo

Serialization
- Text format: yamlcpp
- Binary format: cereal

Configuration:
- yamlcpp
- toml

Asset packing / compression:
- zlib

Misc / notes:
event system is blocking, maybe later need to implement a buffered event system
https://youtu.be/5mlziHwq90k?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&t=478