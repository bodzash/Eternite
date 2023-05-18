#pragma once
#include "Core.hpp"

namespace Engine
{

  class ENGINE_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();
  };

  // To be defined in "client"
  Application* CreateApplication();
  
}