#include <Apex.h>
#include <ApexEntryPoint.h>

class ExampleLayer : public Apex::Layer
{
public:
  ExampleLayer()
    : Layer("Example") {}
  
  void OnUpdate(Apex::Timestep ts) override
  {}

  void OnEvent(Apex::Event& event) override
  {}
};

class GameServer : public Apex::Application
{
public:
  GameServer()
  {
    PushLayer(new ExampleLayer());
  }

  ~GameServer()
  {}
};

Apex::Application* Apex::CreateApplication()
{
  return new GameServer();
}