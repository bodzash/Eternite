#include "Application.hpp"
#include <iostream>
#include "Apex/Events/ApplicationEvent.hpp"
#include "Apex/Log.hpp"

namespace Apex
{
  Application::Application()
  {
  }
  
  Application::~Application()
  {
  }

  void Application::Run()
  {
    WindowResizeEvent e(32, 32);
    if (e.IsInCategory(EventCategoryApplication))
      AX_INFO(e);

    if (e.IsInCategory(EventCategoryKeyboard))
      AX_WARN(e);

    while (true);
  }

}