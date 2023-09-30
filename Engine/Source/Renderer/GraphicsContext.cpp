#include "axpch.h"
#include "GraphicsContext.h"
#include <GLFW/glfw3.h>
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace Apex {

	GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AX_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void GraphicsContext::Init()
	{
		int windowWidth, windowHeight;

		glfwGetWindowSize(m_WindowHandle, &windowWidth, &windowHeight);

		bgfx::Init bgfxInit;
        // TODO: read these in from a file lool
		bgfxInit.platformData.nwh = glfwGetWin32Window(m_WindowHandle);
		bgfxInit.type = bgfx::RendererType::Count;
		bgfxInit.resolution.width = windowWidth;
		bgfxInit.resolution.height = windowHeight;
		bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

		bgfx::init(bgfxInit);

		// should be static or smthing
		const bgfx::ViewId ClearView = 0;
		bgfx::setViewClear(ClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF); //0x443355FF
		bgfx::setViewRect(ClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	}

	void GraphicsContext::SwapBuffers()
	{
		bgfx::frame();
	}

}