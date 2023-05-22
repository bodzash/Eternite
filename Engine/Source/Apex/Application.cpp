#include "axpch.hpp"
#include "Application.hpp"
#include "Apex/Log.hpp"
#include "glad/glad.h"
#include "Input.hpp"

namespace Apex
{
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
      // TEMPORARY
      glClearColor(0.125, 0.21, 0.44, 1);
      glClear(GL_COLOR_BUFFER_BIT);

      for (Layer* layer : m_LayerStack)
        layer->OnUpdate();
      

      // TODO: move to render thread
      m_ImGuiLayer->Begin();
      for (Layer* layer : m_LayerStack)
        layer->OnImGuiRender();
      m_ImGuiLayer->End();

      m_Window->OnUpdate();
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }

  void Application::OnEvent(Event& e)
  {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(AX_BIND_EVENT_FN(Application::OnWindowClose));
    
    //AX_CORE_TRACE("{0}", e);

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
      (*--it)->OnEvent(e);
      if (e.bHandled)
        break;
    }
  }

}