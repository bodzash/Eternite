#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Timestep.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Apex {

	class HeadlessApplication
	{
	public:
		HeadlessApplication();
		virtual ~HeadlessApplication() = default;
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline static HeadlessApplication& Get() { return *s_Instance; }

	private:
		bool m_Running = true;
		LayerStack m_LayerStack;
		static HeadlessApplication* s_Instance;
	};

	// To be defined in Server program
	HeadlessApplication* CreateHeadlessApplication();

}