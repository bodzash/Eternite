#include "axpch.hpp"
#include "OpenGLContext.hpp"
#include <GLFW/glfw3.h>

namespace Apex {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AX_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		//int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//AX_CORE_ASSERT(status, "Failed to initialize Glad!");

    //AX_CORE_INFO("OpenGL Info:");
		//AX_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		//AX_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		//AX_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}