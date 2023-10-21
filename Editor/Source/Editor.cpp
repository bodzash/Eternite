#include <Apex.h>
#include <filesystem>

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;


class EditorLayer : public Layer
{
public:
	EditorLayer()
		: Layer("EditorLayer") {}

	void OnAttach() override
	{
		m_Scene.OnRuntimeStart();
	}

	void OnDetach() override
	{
		m_Scene.OnRuntimeStop();
	}

	void OnUpdate(Timestep ts) override
	{
		m_Scene.OnUpdate(ts);
	}

private:
	Scene m_Scene;
};

class GameEditor : public Application
{
public:
	GameEditor()
	{
		PushLayer(new EditorLayer());
	}
};

Apex::Application* Apex::CreateApplication()
{
	// TODO: ONLY PRESENT IN INTERNAL BUILD, NOT IN DIST
	auto path = std::filesystem::current_path().parent_path().parent_path().parent_path();
	std::filesystem::current_path(path);
	AX_INFO("Path changed: {0}", path);

	return new GameEditor();
}