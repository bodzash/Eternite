//#include <axpch.hpp>
#include <Apex.hpp>
#include "imgui.h"

class ExampleLayer : public Apex::Layer
{
public:
  ExampleLayer()
    : Layer("Example") {}
  
  void OnUpdate(Apex::Timestep ts) override
  {
    AX_INFO("Delta time: {0}s [{1}ms]", ts.GetSeconds(), ts.GetMilliseconds());

    if (Apex::Input::IsKeyPressed(AX_KEY_TAB))
			AX_TRACE("Tab key is pressed (poll)!");
    
  }

  void OnImGuiRender()
  {
    ImGui::Text("Hello World");
  }

  void OnEvent(Apex::Event& event) override
  {

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