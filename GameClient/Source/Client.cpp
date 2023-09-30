#include <Apex.h>
#include <imgui.h>

using namespace Apex;

class GameLayer : public Layer
{
public:
	GameLayer()
		: Layer("GameLayer") {}

	void OnAttach() override
	{
		Entity ent = m_Scene.CreateEntity();
	}

	void OnUpdate(Timestep ts) override
	{
		m_Scene.OnUpdate(ts);
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::KeyPressed)
		{
			AX_TRACE("GameLayer");
			event.Handled = true;
		}
	}

private:
	Scene m_Scene;
};

/*
class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}
	
	int count = 0;

	void OnUpdate(Timestep ts) override	{}

	void OnImGuiRender() override
	{
		ImGui::Text("Count: %d", count);

		if (ImGui::Button("Save"))
			count++;
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::KeyPressed)
			AX_TRACE("ExampleLayer");
	}
};
*/

class GameClient : public Application
{
public:
	GameClient()
	{
		PushLayer(new GameLayer());
	}
};

Apex::Application* Apex::CreateApplication()
{
	return new GameClient();
}