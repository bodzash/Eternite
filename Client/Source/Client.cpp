#include <Apex.h>
#include <ApexEntryPoint.h>
#include <filesystem>
#include "Utils/Utils.h"

namespace Raylib {
	#include <raylib.h>
}

using namespace Apex;

// Bits masked from 0-15 in decimal
enum class CollisionGroup : uint16_t
{
	Group0 = 1,
	Group1 = 2,
	Group2 = 4,
	Group3 = 8,
	Group4 = 16,
	Group5 = 32,
	Group6 = 64,
	Group7 = 128,
	Group8 = 256,
	Group9 = 512,
	Group10 = 1024,
	Group11 = 2048,
	Group12 = 4096,
	Group13 = 8192,
	Group14 = 16384,
	Group15 = 32768
};


class BoxLogic : public NativeScript
{
public:
	int Health = 5;

	void OnDestroy() override
	{
		AX_TRACE("BoxLogic::OnDestroy");
	}
};

class BulletLogic : public NativeScript
{
public:
	float Direction = 0.0f;

	void OnDestroy() override
	{
		AX_TRACE("Dis boolet haz been deztroied :D");
	}

	void OnUpdate(Timestep ts) override
	{
		Get<CRigidBody>().ApplyForce({ 20, 0 });
	}

	void OnCollisionEnter(Entity other) override
	{
		if (other.Has<CScript>())
		{
			if (other.Get<CScript>().Is<BoxLogic>())
			{
				auto& otherScript = other.Get<CScript>().As<BoxLogic>();
				otherScript.Health--;
				AX_TRACE("Other Health: {}", otherScript.Health);
				if (otherScript.Health == 0)
				{
					DestroyEntity(other);
				}
			}
		}

		DestroyEntity(GetSelfEntity());
	}
};

class PlayerLogic : public NativeScript
{
public:
	float Speed = 50.f;
	glm::vec3 LookDir = { 0.f, 0.f, 0.f };

	void OnCreate() override
	{
	}

	void OnUpdate(Timestep ts) override
	{
		auto& tc = Get<CTransform>();
		auto& cc = Get<CCamera>();

		// Look towards mouse
		LookDir = GetScreenFloorRay(Input::GetMousePosition(), cc.Camera);
		tc.Rotation.y = PointDirection(tc.Translation, LookDir);
		tc.Rotation.y += 90.f; // needed cuz model imported improperly

		cc.Camera.position = { tc.Translation.x, 15.f, tc.Translation.z + 7.f };
		cc.Camera.target = { tc.Translation.x, 0.f, tc.Translation.z };

		if (Input::IsKeyPressed(Key::R))
		{
			if (Has<CRigidBody>())
			{
				auto& rbc = Get<CRigidBody>();
				rbc.SetRotation(45);
			}
		}

		if (Input::IsMousePressed(Mouse::Left))
		{
			Entity ent = CreateEntity();
			ent.Get<CTransform>().Translation = tc.Translation;
			ent.Add<CRigidBody>();
			auto& bcc = ent.Add<CBoxCollider>();
			ent.Add<CScript>(new BulletLogic());
			bcc.SetFilterCategory((uint16_t)CollisionGroup::Group2);
			bcc.SetFilterMask((uint16_t)CollisionGroup::Group0);
		}

		if (Input::IsMousePressed(Mouse::Right))
		{
			Remove<CScript>();
		}

		// Movement
		glm::vec2 moveInput = { 0.f, 0.f };
		moveInput.x = (float)Input::IsKeyDown(Key::D) - (float)Input::IsKeyDown(Key::A);
		moveInput.y = (float)Input::IsKeyDown(Key::S) - (float)Input::IsKeyDown(Key::W);
		glm::vec2 move = glm::normalize(moveInput);

		if (moveInput.x || moveInput.y)
		{
			Get<CRigidBody>().ApplyForce({ move.x * Speed, move.y * Speed });
		}

		if (Input::IsKeyPressed(Key::E))
		{
			auto& ass = Get<CScript>().As<PlayerLogic>();
			ass.Speed = 100.f;
		}

		if (Input::IsKeyPressed(Key::Space))
		{
			tc.Translation.x += 3;
		}

		if (Input::IsKeyPressed(Key::Q))
		{
			auto& amc = Get<CModel>();
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
		//AX_TRACE("Collided with: {0}", other.Get<TagComponent>().Tag);
	}
};

class CameraController : public NativeScript
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
			auto& cc = Get<CCamera>();
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
		//cam.Add<CCamera>().Primary = true;
		//cam.Add<ScriptComponent>().Bind<CameraController>();

		// Player
		//Prefabs::Player(m_Scene);

		Entity ent = m_Scene.CreateEntity();
		//ent.Add<ScriptComponent>().Bind<PlayerController>();
		ent.Add<CScript>(new PlayerLogic());
		//ent.Add<CModel>("Data/Models/Characters/Rogue_Hooded.glb",
		//	"Data/Models/Characters/rogue_texture.png", "Data/Models/Characters/Rogue_Hooded.glb");
		ent.Add<CModel>("Data/Models/Characters/Rogue_Hooded.glb",	"Data/Models/Characters/rogue_texture.png");
		auto& rbod = ent.Add<CRigidBody>();
		rbod.OwnRotation = false;
		rbod.SetFixedRotation(true);
		auto& cc = ent.Add<CCircleCollider>();
		cc.SetFilterCategory((uint16_t)CollisionGroup::Group1);
		cc.SetFilterMask((uint16_t)CollisionGroup::Group1 | (uint16_t)CollisionGroup::Group0);
		auto& cam = ent.Add<CCamera>();
		cam.Primary = true;
		cam.Camera.position.x = 0.f;
		cam.Camera.position.y = 15.f;
		cam.Camera.position.z = 7.f;

		// Wall
		Entity wall = m_Scene.CreateEntity();
		//wall.Get<CTransform>().Scale = glm::vec3{ 1.25f, 1.25f, 1.25f };
		auto& rb = wall.Add<CRigidBody>(CRigidBody::BodyType::Static);
		auto& bx = wall.Add<CBoxCollider>(glm::vec2{ 0.f, 0.f }, glm::vec2{ 0.75f, 0.75f });
		bx.SetFilterCategory((uint16_t)CollisionGroup::Group0);
		rb.SetRotation(45);
		rb.OwnRotation = true;
		wall.Get<CTransform>().Rotation.y = 0;
		wall.Add<CModel>("Data/Models/Environment/box_large.gltf.glb");
		wall.Add<CScript>(new BoxLogic());
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
	AX_WARN("Path changed: {0}", path);

	return new GameClient();
}