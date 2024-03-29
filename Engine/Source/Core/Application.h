#pragma once
#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Timestep.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "ImGui/ImGuiLayer.h"

namespace Apex {

	class Application
	{
	public:
		Application();
		virtual ~Application() = default;
		void Run();
		void Close();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline static Application& Get() { return *s_Instance; }

	private:
		//std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.f;
		static Application* s_Instance;

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	// To be defined in Client program
	Application* CreateApplication();

}