#include "axpch.h"
#include "Application.h"
#include "Log.h"
#include "Input.h"

namespace Raylib {
	#include <raylib.h>
}

namespace Apex {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	// TODO: Implement a HeadlessApplication class for server
	Application::Application()
	{
		AX_CORE_ASSERT(!s_Instance, "Application instance already exists!");
		s_Instance = this;

		//m_Window = std::unique_ptr<Window>(Window::Create());
		//m_Window->SetEventCallback(AX_BIND_EVENT_FN(Application::OnEvent));

		Raylib::SetConfigFlags(Raylib::FLAG_WINDOW_RESIZABLE);
    	Raylib::InitWindow(800, 600, "Eternite");
		Raylib::SetTargetFPS(60);

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
			Timestep timestep = Raylib::GetFrameTime();

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			//m_Window->OnUpdate();
			Raylib::BeginDrawing();
            	Raylib::ClearBackground({138, 142, 140, 255});
			Raylib::EndDrawing();

			m_Running = !Raylib::WindowShouldClose();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		// TODO: run some window resize code

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