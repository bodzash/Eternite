//#include <axpch.hpp>
#include <Apex.hpp>
#include "imgui.h"

class ExampleLayer : public Apex::Layer
{
public:
  ExampleLayer()
    : Layer("Example") {}
  
  void OnUpdate(Apex::Timestep ts) override
  {}

  void OnImGuiRender()
  {
    ImGui::ShowDemoWindow();
  }

  void OnEvent(Apex::Event& event) override
  {}

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