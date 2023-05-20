# Apex Game Engine

## Name (very important xD)
- Editor: Forge or Apex Studio or Apex Editor

## Architecture
- Engine - This is a DLL that the Runtime and Editor can link
- Runtime - This is an Executable that links up with the Engine
- Editor - Purely level/prefab editing tool

## Technologies:
Rendering (only one):
- bgfx (most likely)
- diligent (rendering) engine
- I could do raw DX12 or Vulkan but its just too much

Windowing (only one):
- GLFW
- SDL3

3D asset importing:
- AssImp (nice name)
Note: FBX files ONLY

Logging:
- spdlog

Benchmarking and Profiling:
- Cherno's timer class
https://www.youtube.com/watch?v=qiD39bB7DvA&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=56&ab_channel=TheCherno
- chrome profiler stuff

Entity Component System:
- EnTT (not even a question)

Scripting (only one and Native):
- C# with mono as a DLL
- Native with C++ as a DLL

Physics (only one):
- Jolt (most likely because it's aimed at games)

Audio (only one):
- FMOD
- OpenAL

Game GUI/HUD:
- NoesisGUI
Note: Blend tool can be used to create these interfaces

Editor/Game debug GUI:
- DearImgui
- Imguizmo
- Other imgui libraries

Serialization
- Text format: yamlcpp
- Binary format: cereal

Configuration:
- yamlcpp
- ini parser

Asset packing / compression:
- zlib

Testing:
- HAHAHAHAHA

Misc / notes:
precompiled header
event system is blocking, maybe later need to implement a buffered event system
https://youtu.be/5mlziHwq90k?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&t=478