#pragma once
#include "axpch.hpp"
#include "Core.hpp"
#include "Events/Event.hpp"
#include "Renderer/GraphicsContext.hpp"
#include "GLFW/glfw3.h"

namespace Apex
{

  struct WindowProps
  {
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    WindowProps(const std::string& title = "Apex Engine", unsigned int width = 800, unsigned int height = 600)
      : Title(title), Width(width), Height(height) {}
  };

  // Interface representing a desktop window
  class Window
  {
  public:
    using EventCallbackFn = std::function<void(Event&)>;

    ~Window();

    void Init(const WindowProps& props);
    void Shutdown();

    void OnUpdate();

    unsigned int GetWidth() const;
    unsigned int GetHeight() const;

    // Window attributes
    void SetEventCallback(const EventCallbackFn& callback);
    void SetVSync(bool enabled);
    bool IsVSync() const;
    void* GetNativeWindow() const;

    static Window* Create(const WindowProps& props = WindowProps());

private:
    Window(const WindowProps& props);

    GLFWwindow* m_Window;
    GraphicsContext* m_Context;

    struct WindowData
    {
      std::string Title;
      unsigned int Width, Height;
      bool VSync;

      EventCallbackFn EventCallback;
    };

    WindowData m_Data;
  };
  

};