#include <Apex.h>
#include <filesystem>

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
		if (Raylib::IsKeyPressed(Raylib::KEY_F))
		{
			auto& tc = GetComponent<TransformComponent>();
			tc.Translation.x += 12.f * ts;
		}
	}

	void OnDestroy() override
	{
	}
};

class CameraController : public NativeBehaviour
{
public:
	bool Enabled = false;

	void OnCreate() override
	{
	}

	void OnUpdate(Timestep ts) override
	{
		if (Raylib::IsMouseButtonPressed(Raylib::MOUSE_BUTTON_RIGHT))
		{
			Enabled = !Enabled;

			if (Enabled)
			{
				Raylib::HideCursor();
				Raylib::DisableCursor();
			}
			else
			{
				Raylib::ShowCursor();
				Raylib::EnableCursor();
			}
		}

		if (Enabled)
		{
			auto& cc = GetComponent<CameraComponent>();
			Raylib::UpdateCamera(&cc.Camera, Raylib::CAMERA_FREE);
		}
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
		ent.AddComponent<MeshComponent>("Data/Models/Leblanc/Leblanc_Skin04.gltf",
			"Data/Models/Leblanc/leblanc_Skin04_TX_CM.png");
		ent.AddComponent<RigidBodyComponent>();
		ent.AddComponent<BoxColliderComponent>();

		Entity wall = m_Scene.CreateEntity();
		wall.AddComponent<RigidBodyComponent>(RigidBodyComponent::BodyType::Static);
		wall.AddComponent<BoxColliderComponent>(glm::vec2{ 0.f, 0.f }, glm::vec2{ 1.f, 1.f });

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
	// TODO: ONLY PRESENT IN DEBUG, BECAUSE OF CMAKE >:|
	auto path = std::filesystem::current_path().parent_path().parent_path().parent_path();
	std::filesystem::current_path(path);
	AX_INFO("Path changed: {0}", path);

	return new GameClient();
}