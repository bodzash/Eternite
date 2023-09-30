#include "axpch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"
#include <glfw/glfw3.h>
#include "bgfx/bgfx.h"

namespace Apex {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AX_CORE_ASSERT(!s_Instance, "Application instance already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(AX_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// TODO: shouldnt be here
			bgfx::touch(0);

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}
			
			// TODO: something
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		// TODO: should create a window method and gfx context methods to handle this :)
		std::int32_t displayWidth, displayHeight;
		glfwGetFramebufferSize((GLFWwindow*)m_Window->GetNativeWindow(), &displayWidth, &displayHeight);
		bgfx::reset(displayWidth, displayHeight, BGFX_RESET_VSYNC);
		bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

		return true;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(AX_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(AX_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			break;
		}
	}

}