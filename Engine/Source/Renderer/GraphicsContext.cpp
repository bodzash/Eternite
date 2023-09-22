#include "axpch.hpp"
#include "GraphicsContext.hpp"
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
        // TODO:
		bgfxInit.platformData.nwh = glfwGetWin32Window(m_WindowHandle);
		bgfxInit.type = bgfx::RendererType::Count;
		bgfxInit.resolution.width = windowWidth;
		bgfxInit.resolution.height = windowHeight;
		bgfxInit.resolution.reset = BGFX_RESET_VSYNC;

		bgfx::init(bgfxInit);

		const bgfx::ViewId kClearView = 0;
		bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF); //0x443355FF
		bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	}

	void GraphicsContext::SwapBuffers()
	{
		//glfwSwapBuffers(m_WindowHandle);
	}

}