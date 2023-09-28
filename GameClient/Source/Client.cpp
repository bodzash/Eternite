#include <Apex.hpp>
#include "imgui.h"

class ExampleLayer : public Apex::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate(Apex::Timestep ts) override {}

	void OnImGuiRender()
	{
		ImGui::ShowDemoWindow();
	}

	void OnEvent(Apex::Event& event) override {}
};

class GameClient : public Apex::Application
{
public:
	GameClient()
	{
		PushLayer(new ExampleLayer());
	}

	~GameClient() {}
};

Apex::Application* Apex::CreateApplication()
{
	return new GameClient();
}