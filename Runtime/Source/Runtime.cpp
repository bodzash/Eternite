//#include <axpch.hpp>
#include <Apex.hpp>

class ExampleLayer : public Apex::Layer
{
public:
  ExampleLayer()
    : Layer("Example") {}
  
  void OnUpdate() override
  {
    //AX_INFO("ExampleLayer::OnUpdate");
    if (Apex::Input::IsKeyPressed(AX_KEY_TAB))
			AX_TRACE("Tab key is pressed (poll)!");
  }

  void OnEvent(Apex::Event& event) override
  {
    //AX_TRACE("{0}", event);

    if (event.GetEventType() == Apex::EventType::KeyPressed)
    {
      Apex::KeyPressedEvent& e = (Apex::KeyPressedEvent&)event;
      if (e.GetKeyCode() == AX_KEY_TAB)
				AX_TRACE("Tab key is pressed (event)!");
			AX_TRACE("{0}", (char)e.GetKeyCode());
    }
  }
};

class Runtime : public Apex::Application
{
public:
  Runtime()
  {
    PushLayer(new ExampleLayer());
    PushOverlay(new Apex::ImGuiLayer());
  }

  ~Runtime()
  {

  }
};

Apex::Application* Apex::CreateApplication()
{
  return new Runtime();
}