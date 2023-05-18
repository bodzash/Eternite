#include <iostream>
#include <Engine.hpp>

class Runtime : public Engine::Application
{
public:
  Runtime() {}
  ~Runtime() {}
};

Engine::Application* Engine::CreateApplication()
{
  return new Runtime();
}