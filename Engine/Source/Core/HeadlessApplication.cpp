#include "axpch.h"
#include "HeadlessApplication.h"
#include "Log.h"

namespace Apex {

	#define BIND_EVENT_FN(x) std::bind(&HeadlessApplication::x, this, std::placeholders::_1)

	HeadlessApplication* HeadlessApplication::s_Instance = nullptr;

	HeadlessApplication::HeadlessApplication()
	{
		AX_CORE_ASSERT(!s_Instance, "HeadlessApplication instance already exists!");
		s_Instance = this;

		// Setup a "window" and set this trhread to run 60fps
	}

	void HeadlessApplication::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void HeadlessApplication::Run()
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

	void HeadlessApplication::OnEvent(Event& e)
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