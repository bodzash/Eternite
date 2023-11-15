#include <Apex.h>
#include <ApexEntryPoint.h>
#include <filesystem>
#include "Utils/Utils.h"

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

enum class CollisionGroup : uint16_t
{
	None = 0,
	World = 1 << 1,
	Team0 = 1 << 2,
	Team1 = 1 << 3,
	Team2 = 1 << 4
};

class BulletLogic : public NativeBehaviour
{
public:
	void OnUpdate(Timestep ts) override
	{
		GetComponent<RigidBodyComponent>().ApplyForce({ 20, 0 });
	}
};

class PlayerLogic : public NativeBehaviour
{
public:
	float Speed = 50.f;
	glm::vec3 LookDir = { 0.f, 0.f, 0.f };

	void OnCreate() override
	{
	}

	void OnUpdate(Timestep ts) override
	{
		auto& tc = GetComponent<TransformComponent>();
		auto& cc = GetComponent<CameraComponent>();

		// Look towards mouse
		LookDir = GetScreenFloorRay(Input::GetMousePosition(), cc.Camera);
		tc.Rotation.y = PointDirection(tc.Translation, LookDir);
		tc.Rotation.y += 90.f; // needed cuz model imported improperly

		cc.Camera.position = { tc.Translation.x, 10.f, tc.Translation.z + 9.f };
		cc.Camera.target = { tc.Translation.x, 0.f, tc.Translation.z };

		if (Input::IsKeyPressed(Key::R))
		{
			if (HasComponent<RigidBodyComponent>())
			{
				auto& rbc = GetComponent<RigidBodyComponent>();
				rbc.SetRotation(45);
			}
		}

		if (Input::IsMousePressed(Mouse::Left))
		{
			Entity ent = CreateEntity();
			ent.GetComponent<TransformComponent>().Translation = tc.Translation;
			ent.AddComponent<BehaviourComponent>(new BulletLogic());
			ent.AddComponent<RigidBodyComponent>();
			ent.AddComponent<BoxColliderComponent>();
		}

		if (Input::IsMousePressed(Mouse::Right))
		{
			RemoveComponent<BehaviourComponent>();
			//RemoveComponent<ScriptComponent>();
		}

		// Movement
		glm::vec2 moveInput = { 0.f, 0.f };
		moveInput.x = (float)Input::IsKeyDown(Key::D) - (float)Input::IsKeyDown(Key::A);
		moveInput.y = (float)Input::IsKeyDown(Key::S) - (float)Input::IsKeyDown(Key::W);
		glm::vec2 move = glm::normalize(moveInput);

		if (moveInput.x || moveInput.y)
			GetComponent<RigidBodyComponent>().ApplyForce({ move.x * Speed, move.y * Speed });

		if (Input::IsKeyPressed(Key::E))
		{
			auto& ass = GetComponent<BehaviourComponent>().As<PlayerLogic>();
			ass.Speed = 100.f;
		}

		if (Input::IsKeyPressed(Key::Q))
		{
			auto& amc = GetComponent<ModelComponent>();
			amc.AnimIndex++;
			if (amc.AnimIndex > amc.AnimsCount - 1)
			{
				amc.AnimIndex = 0;
			}
			amc.AnimCurrentFrame = 0;
		}
	}

	void OnCollisionEnter(Entity other) override
	{
		AX_TRACE("Collided with: {0}", other.GetComponent<TagComponent>().Tag);
	}

	void OnDestroy() override
	{
		AX_TRACE("Script OnDestroy");
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
		if (Input::IsMousePressed(Mouse::Right))
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
		//Entity cam = m_Scene.CreateEntity();
		//cam.AddComponent<CameraComponent>().Primary = true;
		//cam.AddComponent<ScriptComponent>().Bind<CameraController>();

		// Player
		Entity ent = m_Scene.CreateEntity();
		//ent.AddComponent<ScriptComponent>().Bind<PlayerController>();
		ent.AddComponent<BehaviourComponent>(new PlayerLogic());
		//ent.AddComponent<ModelComponent>("Data/Models/Characters/Rogue_Hooded.glb",
		//	"Data/Models/Characters/rogue_texture.png", "Data/Models/Characters/Rogue_Hooded.glb");
		ent.AddComponent<ModelComponent>("Data/Models/Characters/Rogue_Hooded.glb",	"Data/Models/Characters/rogue_texture.png");
		auto& rbod = ent.AddComponent<RigidBodyComponent>();
		rbod.OwnRotation = false;
		rbod.SetFixedRotation(true);
		auto& cc = ent.AddComponent<CircleColliderComponent>();
		cc.SetFilterCategory(3);
		cc.SetFilterMask(4);
		auto& cam = ent.AddComponent<CameraComponent>();
		cam.Primary = true;
		cam.Camera.position.x = 0.f;
		cam.Camera.position.y = 10.f;
		cam.Camera.position.z = 10.f;

		// Wall
		Entity wall = m_Scene.CreateEntity();
		//wall.GetComponent<TransformComponent>().Scale = glm::vec3{ 1.25f, 1.25f, 1.25f };
		wall.AddComponent<RigidBodyComponent>(RigidBodyComponent::BodyType::Static);
		auto& bx = wall.AddComponent<BoxColliderComponent>(glm::vec2{ 0.f, 0.f }, glm::vec2{ 1.f, 1.f });
		bx.SetFilterCategory(1);
		bx.SetFilterMask(2);
		wall.AddComponent<ModelComponent>("Data/Models/Environment/box_large.gltf.glb");
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