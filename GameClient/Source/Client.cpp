#include <Apex.h>
#include <filesystem>

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

class PlayerController : public NativeBehaviour
{
public:
	float Speed = 3.f;

	void OnCreate() override
	{
	}

	void OnUpdate(Timestep ts) override
	{
		auto& tc = GetComponent<TransformComponent>();

		if (Input::IsKeyPressed(Key::F))
		{
			RemoveComponent<RigidBodyComponent>();
			RemoveComponent<BoxColliderComponent>();
		}

		if (Input::IsKeyPressed(Key::G))
		{
			if (!HasComponent<RigidBodyComponent>())
			{
				auto& rbc = AddComponent<RigidBodyComponent>();
				AddComponent<BoxColliderComponent>();

				//rbc.SetTransform({tc.Translation.x + 5, 0, tc.Translation.z + 5}, 45);
			}
		}

		if (Input::IsKeyPressed(Key::R))
		{
			if (HasComponent<RigidBodyComponent>())
			{
				auto& rbc = GetComponent<RigidBodyComponent>();
				rbc.SetRotation(45);
			}
		}

		if (Raylib::IsKeyDown(Key::W))
			tc.Translation.z -= Speed * ts;

		if (Raylib::IsKeyDown(Key::S))
			tc.Translation.z += Speed * ts;

		if (Raylib::IsKeyDown(Key::A))
			tc.Translation.x -= Speed * ts;

		if (Raylib::IsKeyDown(Key::D))
			tc.Translation.x += Speed * ts;

		// Rot
		if (Raylib::IsKeyDown(Key::Q))
			tc.Rotation.y += Speed * 100.f * ts;
		
		if (Raylib::IsKeyDown(Key::E))
			tc.Rotation.y -= Speed * 100.f * ts;
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
		if (Raylib::IsMouseButtonPressed(Mouse::Right))
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
		m_Scene.OnRuntimeStart();

		// Scene Camera
		Entity cam = m_Scene.CreateEntity();
		cam.AddComponent<CameraComponent>().Primary = true;
		cam.AddComponent<ScriptComponent>().Bind<CameraController>();

		// Player
		Entity ent = m_Scene.CreateEntity();
		ent.AddComponent<ScriptComponent>().Bind<PlayerController>();
		ent.AddComponent<ModelComponent>("Data/Models/Leblanc/Leblanc_Skin04.gltf",
			"Data/Models/Leblanc/leblanc_Skin04_TX_CM.png");
		ent.AddComponent<RigidBodyComponent>();
		ent.AddComponent<BoxColliderComponent>();

		// Wall
		Entity wall = m_Scene.CreateEntity();
		wall.AddComponent<RigidBodyComponent>(RigidBodyComponent::BodyType::Static);
		wall.AddComponent<BoxColliderComponent>(glm::vec2{ 0.f, 0.f }, glm::vec2{ 1.f, 1.f });
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
	// TODO: ONLY PRESENT IN INTERNAL BUILD, NOT IN DIST
	auto path = std::filesystem::current_path().parent_path().parent_path().parent_path();
	std::filesystem::current_path(path);
	AX_INFO("Path changed: {0}", path);

	return new GameClient();
}