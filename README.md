# Apex Game Engine

## Name (very important xD)
- Editor: Forge or Apex Studio or Apex Editor

## Architecture
- Engine - This is a DLL that the Runtime and Editor can link
- Runtime - This is an Executable that links up with the Engine
- Editor - Purely level/prefab editing tool

## Technologies:
Rendering (only one):
- bgfx *

Windowing (only one):
- GLFW
- SDL3 *

3D asset importing:
- AssImp * (nice name)
Note: FBX files ONLY

Logging:
- spdlog *

Benchmarking and Profiling:
- Cherno's timer class
https://www.youtube.com/watch?v=qiD39bB7DvA&list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&index=56&ab_channel=TheCherno
- chrome profiler tool

Entity Component System:
- EnTT * (not even a question)

Scripting (only one):
- C# with Mono
- Lua with Sol3 *
- AngelScript

Physics (only one):
- Jolt * (most likely because it's aimed at games)

Audio (only one):
- FMOD *
- OpenAL

Game GUI/HUD:
- NoesisGUI *
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
event system is blocking, maybe later need to implement a buffered event system
https://youtu.be/5mlziHwq90k?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&t=478

```cpp
//#define GLFW_INCLUDE_NONE
#include <iostream>
#include <GLFW/glfw3.h>
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

static void glfw_errorCallback(int error, const char *description)
{
	fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

int main(int argc, char **argv)
{
  glfwSetErrorCallback(glfw_errorCallback);
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window = glfwCreateWindow(800, 600, "Hello, bgfx!", nullptr, nullptr);

  bgfx::Init bgfxInit;
  bgfxInit.platformData.nwh = glfwGetWin32Window(window);
  bgfxInit.type = bgfx::RendererType::Count;
  bgfxInit.resolution.width = 800;
  bgfxInit.resolution.height = 600;
  bgfxInit.resolution.reset = BGFX_RESET_VSYNC;
  
  if (!bgfx::init(bgfxInit))
  {
    std::cout << "SADASDAS \n";
    std::cin.get();
  }

  // Create a view and set it to the same dimensions as the window
  const bgfx::ViewId kClearView = 0;
  bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR, 0x443355FF);
  bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);

  // Alternative
  /*
  bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
  bgfx::setViewRect(0, 0, 0, 800, 600);
  */

  while(!glfwWindowShouldClose(window))
  {
    // Polls events
    glfwPollEvents();

    // This dummy draw call is here to make sure that view 0 is cleared if no other draw calls are submitted to view 0.
    bgfx::touch(kClearView);

    // Rendering here, this is some dummy debug bs
    bgfx::dbgTextClear();
    bgfx::dbgTextPrintf(0, 0, 0x0f, "Press F1 to toggle stats.");

    // Enable stats or debug text. BGFX_DEBUG_STATS or BGFX_DEBUG_TEXT
    bgfx::setDebug(BGFX_DEBUG_TEXT);

    // Advance to next frame. Process submitted rendering primitives.
    bgfx::frame();
  }

  bgfx::shutdown();
  glfwDestroyWindow(window);
  glfwTerminate();
}
```