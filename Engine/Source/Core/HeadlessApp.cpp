#include "axpch.h"
#include "HeadlessApp.h"
#include "Log.h"

namespace Apex {

	#define BIND_EVENT_FN(x) std::bind(&HeadlessApp::x, this, std::placeholders::_1)

	HeadlessApp* HeadlessApp::s_Instance = nullptr;

	HeadlessApp::HeadlessApp()
	{
		AX_CORE_ASSERT(!s_Instance, "HeadlessApp instance already exists!");
		s_Instance = this;

		// Setup a "window" and set this trhread to run 60fps
	}

	void HeadlessApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void HeadlessApp::Run()
	{
		while (m_Running)
		{
			// Get frame time here
            Timestep timestep = 0.0f;

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(timestep);
			}

			// Run main loop here

            // Something should querry this?
            m_Running = true;
		}
	}

	void HeadlessApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
        // Dispatch binded event shit like this:
		//dispatcher.Dispatch<WindowCloseEvent>(AX_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
			break;
		}
	}

}