//#include <axpch.hpp>
#include <Apex.hpp>

class ExampleLayer : public Apex::Layer
{
public:
  ExampleLayer()
    : Layer("Example") {}
  
  void OnUpdate() override
  {
    AX_INFO("ExampleLayer::OnUpdate");
  }

  void OnEvent(Apex::Event& event) override
  {
    AX_TRACE("{0}", event);
  }
};

class Runtime : public Apex::Application
{
public:
  Runtime()
  {
    PushLayer(new ExampleLayer());
  }

  ~Runtime()
  {

  }
};

Apex::Application* Apex::CreateApplication()
{
  return new Runtime();
}