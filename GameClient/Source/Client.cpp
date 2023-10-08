#include <Apex.h>

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

class PlayerController : public NativeBehaviour
{
public:
	void OnCreate() override
	{
	}

	void OnUpdate(Timestep ts) override
	{
	}

	void OnDestroy() override
	{
	}
};

class CameraController : public NativeBehaviour
{
public:
	void OnCreate() override
	{
	}

	void OnUpdate(Timestep ts) override
	{
		auto& cc = GetComponent<CameraComponent>();
		Raylib::UpdateCamera(&cc.Camera, Raylib::CAMERA_FREE);
	}

	void OnDestroy() override
	{
	}
};

class GameLayer : public Layer
{
public:
	GameLayer()
		: Layer("GameLayer") {}

	void OnAttach() override
	{
		Entity cam = m_Scene.CreateEntity();
		cam.AddComponent<CameraComponent>().Primary = true;
		cam.AddComponent<ScriptComponent>().Bind<CameraController>();

		Entity ent = m_Scene.CreateEntity();
		ent.AddComponent<ScriptComponent>().Bind<PlayerController>();
		ent.AddComponent<MeshComponent>("Leblanc_Skin04.gltf");
	}

	void OnUpdate(Timestep ts) override
	{
		m_Scene.OnUpdate(ts);
	}

private:
	Scene m_Scene;
};

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