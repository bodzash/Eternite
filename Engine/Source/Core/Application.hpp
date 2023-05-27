#pragma once
#include "Core.hpp"
#include "Window.hpp"
#include "Apex/LayerStack.hpp"
#include "Apex/Events/Event.hpp"
#include "Apex/Events/ApplicationEvent.hpp"
#include "Apex/ImGui/ImGuiLayer.hpp"
#include "Apex/Core/Timestep.hpp"

namespace Apex
{

  class Application
  {
  public:
    Application();
    virtual ~Application() = default;
    void Run();
    void OnEvent(Event& e);
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);
    inline static Application& Get() { return *s_Instance; }
    inline Window& GetWindow() { return *m_Window; }
  private:
    bool OnWindowClose(WindowCloseEvent& e);

  private:
    std::unique_ptr<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bool m_Running = true;
    LayerStack m_LayerStack;
    float m_LastFrameTime = 0.f;
    static Application* s_Instance;
  };

  // To be defined in "client"
  Application* CreateApplication();
  
}