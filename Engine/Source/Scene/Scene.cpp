#include "axpch.h"
#include "Scene.h"
#include "Scene/Components.h"
#include "Scene/ComponentsGraphic.h"
#include "Scene/Entity.h"
#include <glm/glm.hpp>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

namespace Apex {

// Template specialization must be defined before usage
#pragma region ComponentLifeCycle

    template<>
	void Scene::OnComponentAdded<RigidBodyComponent>(entt::entity e)
	{
        AX_CORE_INFO("Created RigidBodyComponent on {0}", (uint32_t)entity);
	}

    template<>
	void Scene::OnComponentRemoved<RigidBodyComponent>(entt::entity e)
	{
        AX_CORE_WARN("Removed RigidBodyComponent on {0}", (uint32_t)entity);
	}

#pragma endregion

    Scene::Scene(/* args */)
    {
        // Physics
        m_Registry.on_construct<RigidBodyComponent>().connect<&Scene::OnComponentAdded<RigidBodyComponent>>(this);
        m_Registry.on_destroy<RigidBodyComponent>().connect<&Scene::OnComponentRemoved<RigidBodyComponent>>(this);
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TransformComponent>();

        auto tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Unknown" : name;

        // TODO: should create relation component here :)

        return entity;
    }

	void Scene::OnRuntimeStart()
    {
        m_PhysicsWorld = new b2World({ 0.f, 0.f });

        // Should do this when a component gets created
        auto view = m_Registry.view<TransformComponent, RigidBodyComponent>();
        for (auto e : view)
        {
            Entity entity = { e, this };
            auto& tc = entity.GetComponent<TransformComponent>();
            auto& rbc = entity.GetComponent<RigidBodyComponent>();

            b2BodyDef bodyDef;
            bodyDef.type = (b2BodyType)rbc.Type;
            bodyDef.position.Set(tc.Translation.x, tc.Translation.z);
            bodyDef.angle = tc.Rotation.y;
            // ...
            // add user data and thingsx like that

            b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
            body->SetFixedRotation(rbc.FixedRotation);
            // ...
            rbc.RuntimeBody = body;

            if (entity.HasComponent<BoxColliderComponent>())
            {
                auto& bcc = entity.GetComponent<BoxColliderComponent>();

                b2PolygonShape shape;
                shape.SetAsBox(tc.Scale.x * bcc.Size.x, tc.Scale.z * bcc.Size.y);

                b2FixtureDef fixtureDef;
                fixtureDef.shape = &shape;
                fixtureDef.density = bcc.Density;
                fixtureDef.friction = bcc.Friction;
                fixtureDef.restitution = bcc.Restitution;
                fixtureDef.restitutionThreshold = bcc.RestitutionThreshold;
                body->CreateFixture(&fixtureDef);
            }
        }
    }

	void Scene::OnRuntimeStop()
    {
        delete m_PhysicsWorld;
        m_PhysicsWorld = nullptr;
    }

	void Scene::OnUpdate(Timestep ts)
	{
		// Update scripts
        {
            m_Registry.view<ScriptComponent>().each([=](auto entity, auto& sc)
            {
                // TODO: move to OnStart, or rather OnComponentAdded<ScriptComponent>
                // TODO: call destroy on this when OnComponentRemoved<ScriptComponent>
                // ... need to use entt's bullshit for this, and call it when OnStop
                if (!sc.Instance)
                {
                    sc.Instance = sc.InstantiateScript();
                    sc.Instance->m_Entity = Entity{ entity, this };
                    sc.Instance->OnCreate();
                }
                
                sc.Instance->OnUpdate(ts);
            });
        }

        // Physics
        {
            const int32_t velocityIteration = 6;
            const int32_t positionIteration = 2;
            m_PhysicsWorld->Step(ts, velocityIteration, positionIteration);

            // Retrieve transforms
            auto view = m_Registry.view<RigidBodyComponent>();
            for (auto e : view)
            {
                Entity entity = { e, this };
                
                auto& tc = entity.GetComponent<TransformComponent>();
                auto& rbc = entity.GetComponent<RigidBodyComponent>();

                b2Body* body = static_cast<b2Body*>(rbc.RuntimeBody);
                const auto& pos = body->GetPosition();
                tc.Translation.x = pos.x;
                tc.Translation.z = pos.y;
                tc.Rotation.y = body->GetAngle();
            }
        }

        // Rendering
        {
            Raylib::BeginDrawing();
            Raylib::ClearBackground({138, 142, 140, 255});

            Raylib::Camera3D* mainCamera = nullptr;
            TransformComponent cameraTransform;
            {
                auto view = m_Registry.view<TransformComponent, CameraComponent>();
                for (auto e : view)
                {
                    auto [transform, camera] = view.get<TransformComponent, CameraComponent>(e);

                    if (camera.Primary)
                    {
                        mainCamera = &camera.Camera;
                        cameraTransform = transform;
                        break;
                    }
                }
            }

            if (mainCamera)
            {
                Raylib::BeginMode3D(*mainCamera);
                Raylib::DrawGrid(20, 1.0f);

                // Mesh rendering
                {
                    auto view = m_Registry.view<TransformComponent, MeshComponent>();
                    for (auto e : view)
                    {
                        auto [tf, mesh] = view.get<TransformComponent, MeshComponent>(e);
                        // TODO: use the Ex version or someshit
                        Raylib::DrawModel(mesh.Model,
                            { tf.Translation.x, tf.Translation.y, tf.Translation.z },
                            0.005f, {255, 255, 255, 255});
                    }
                }

                // Debug BoxCollider
                {
                    auto view = m_Registry.view<TransformComponent, BoxColliderComponent>();
                    for (auto e : view)
                    {
                        auto [tf, box] = view.get<TransformComponent, BoxColliderComponent>(e);
                        Raylib::DrawCubeWiresV({ tf.Translation.x, tf.Translation.y + 0.5f, tf.Translation.z},
                            { box.Size.x, 1.0f, box.Size.y }, {255, 255, 255, 255});
                    }
                }
                Raylib::EndMode3D();
            }
            else
            {
                AX_CORE_WARN("There is no camera present in the scene!");
            }
			Raylib::EndDrawing();
        }
	}

}