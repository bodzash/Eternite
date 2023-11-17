#pragma once
#include "Core.h"
#include "LayerStack.h"
#include "Timestep.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

namespace Apex {

	class HeadlessApp
	{
	public:
		HeadlessApp();
		virtual ~HeadlessApp() = default;
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline static HeadlessApp& Get() { return *s_Instance; }

	private:
		bool m_Running = true;
		LayerStack m_LayerStack;
		static HeadlessApp* s_Instance;
	};

	// To be defined in Server program
	HeadlessApp* CreateHeadlessApp();

}