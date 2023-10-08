#pragma once

// Forward decl
struct GLFWwindow;

namespace Apex {

	class GraphicsContext
	{
	public:
		GraphicsContext(/*GLFWwindow* windowHandle*/);

		void Init();
		void SwapBuffers();

	private:
		//GLFWwindow* m_WindowHandle;
	};

}