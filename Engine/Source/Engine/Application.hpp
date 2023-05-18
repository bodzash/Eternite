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
  
}