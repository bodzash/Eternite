#include "Application.hpp"
#include <iostream>

namespace Engine
{
  Application::Application()
  {
  }
  
  Application::~Application()
  {
  }

  void Application::Run()
  {
    while (true)
    {
      std::cout << "Engine loop\n";
    }
  }

}