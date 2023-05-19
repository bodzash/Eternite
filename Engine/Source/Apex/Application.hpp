#pragma once
#include "Core.hpp"
#include "Events/Event.hpp"
#include "Apex/Events/ApplicationEvent.hpp"
#include "Window.hpp"

namespace Apex
{

  class APEX_API Application
  {
  public:
    Application();
    virtual ~Application();
    void Run();
    void OnEvent(Event& e);
  private:
    bool OnWindowClose(WindowCloseEvent& e);

  private:
    std::unique_ptr<Window> m_Window;
    bool m_Running = true;
  };

  // To be defined in "client"
  Application* CreateApplication();
  
}