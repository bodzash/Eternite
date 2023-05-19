#pragma once
#include "Core.hpp"
#include "Window.hpp"
#include "Apex/LayerStack.hpp"
#include "Apex/Events/Event.hpp"
#include "Apex/Events/ApplicationEvent.hpp"

namespace Apex
{

  class APEX_API Application
  {
  public:
    Application();
    virtual ~Application();
    void Run();
    void OnEvent(Event& e);
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);
  private:
    bool OnWindowClose(WindowCloseEvent& e);

  private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
    LayerStack m_LayerStack;
  };

  // To be defined in "client"
  Application* CreateApplication();
  
}