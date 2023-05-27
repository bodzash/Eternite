# Apex Game Engine
A 3D FPS focused game engine

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