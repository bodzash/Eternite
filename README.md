# Unnamed Game Engine

## Names (very important xD)
Engine: Nuclear, Atom
Editor: Forge

## Architecture
Engine - This is a DLL that the Runtime and Editor can link
Runtime - This is an Executable that links up with the Engine
Editor - Purely level/prefab editing tool

## Technologies:
Rendering (only one):
- raylib (temporary)
- DirectX12 (limits to Windows and Xbox)
- OpenGl 4+ (Windows, Linux, Mac, Android, Steam Deck, Nintendo Switch)
- Vulkan (Windows, Linux, Android, Steam Deck?, Nintendo Switch, with Molten SDK: Mac, iOS)

Windowing (only one):
- Windows API (in case of DirectX12)
- GLFW (in case of Vulkan or OpenGL)

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
- Lua with sol2
- C# with mono as a DLL
- AngelScript with ???
- Native with C++ as a DLL

Physics (only one):
- Jolt (most likely because it's aimed at games)
- NVIDIA PhysX (documentation kinda shit)
- Bullet3 (lol no)

Audio (only one):
- rayaudio (temporary)
- FMOD
- OpenAL

Networking (probably not gonna implement):
- Steamworks or GameNetworkingSockets
- ENet (no encryption)
- Riptide (C# library) (in case of C# is the scripting lang)

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
- ini parser (idk)

Asset packing / compression:
- zlib

Testing:
- HAHAHAHAHA

Misc / notes:
precompiled header