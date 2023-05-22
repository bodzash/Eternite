#pragma once

#include "Apex/Renderer/GraphicsContext.hpp"

// forward decl
struct GLFWwindow;

namespace Apex {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}