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
#include <box2d/b2_circle_shape.h>

namespace Raylib {
    #include <rlgl.h>
}

namespace Apex {

static bool s_DebugRender = false;

// Template specialization must be defined before usage very unfortunate :(
#pragma region ComponentLifeCycle

#pragma region RigidBodyComponent
    template<>
	void Scene::OnComponentAdded<RigidBodyComponent>(entt::entity e)
	{
        Entity entity = { e, this };
        auto& tc = entity.GetComponent<TransformComponent>();
        auto& rbc = entity.GetComponent<RigidBodyComponent>();

        b2BodyDef bodyDef;
        bodyDef.type = (b2BodyType)rbc.Type;
        bodyDef.position.Set(tc.Translation.x, tc.Translation.z);
        bodyDef.angle = glm::radians(tc.Rotation.y);
        bodyDef.linearDamping = rbc.LinearDamping;
        // ...

        b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
        body->SetFixedRotation(rbc.FixedRotation);
        body->GetUserData().pointer = (uintptr_t)e;
        // ...

        rbc.RuntimeBody = body;
	}

    template<>
	void Scene::OnComponentRemoved<RigidBodyComponent>(entt::entity e)
	{
        Entity entity = { e, this };
        auto& rbc = entity.GetComponent<RigidBodyComponent>();
        m_PhysicsWorld->DestroyBody(rbc.RuntimeBody);

        // TODO: should delete collider components as well since fixtures are axed too
        if (entity.HasComponent<BoxColliderComponent>())
        {
            entity.RemoveComponent<BoxColliderComponent>();
        }

        if (entity.HasComponent<CircleColliderComponent>())
        {
            entity.RemoveComponent<CircleColliderComponent>();
        }
	}
#pragma endregion

#pragma region BoxColliderComponent
    template<>
	void Scene::OnComponentAdded<BoxColliderComponent>(entt::entity e)
	{
        Entity entity = { e, this };
        auto& tc = entity.GetComponent<TransformComponent>();
        auto& bcc = entity.GetComponent<BoxColliderComponent>();

        if (entity.HasComponent<RigidBodyComponent>())
        {
            auto& rbc = entity.GetComponent<RigidBodyComponent>();

            b2PolygonShape shape;
            shape.SetAsBox(tc.Scale.x * bcc.Size.x, tc.Scale.z * bcc.Size.y);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density = bcc.Density;
            fixtureDef.friction = bcc.Friction;
            fixtureDef.restitution = bcc.Restitution;
            fixtureDef.restitutionThreshold = bcc.RestitutionThreshold;
            rbc.RuntimeBody->CreateFixture(&fixtureDef);
        }
        else
        {
            AX_ASSERT(false, "Before adding BoxColliderComponent, RigidBodyComponent must be present!");
        }
    }

    template<>
	void Scene::OnComponentRemoved<BoxColliderComponent>(entt::entity e)
	{
	}
#pragma endregion

#pragma region CircleColliderComponent
    template<>
	void Scene::OnComponentAdded<CircleColliderComponent>(entt::entity e)
	{
        Entity entity = { e, this };
        auto& tc = entity.GetComponent<TransformComponent>();
        auto& ccc = entity.GetComponent<CircleColliderComponent>();

        if (entity.HasComponent<RigidBodyComponent>())
        {
            auto& rbc = entity.GetComponent<RigidBodyComponent>();

            b2CircleShape shape;
            //shape.SetAsCircle();
            shape.m_radius = ccc.Radius;
            //shape.SetAsBox(tc.Scale.x * bcc.Size.x, tc.Scale.z * bcc.Size.y);

            b2FixtureDef fixtureDef;
            fixtureDef.shape = &shape;
            fixtureDef.density = ccc.Density;
            fixtureDef.friction = ccc.Friction;
            fixtureDef.restitution = ccc.Restitution;
            fixtureDef.restitutionThreshold = ccc.RestitutionThreshold;
            rbc.RuntimeBody->CreateFixture(&fixtureDef);
        }
        else
        {
            AX_ASSERT(false, "Before adding CircleColliderComponent, RigidBodyComponent must be present!");
        }
    }

    template<>
	void Scene::OnComponentRemoved<CircleColliderComponent>(entt::entity e)
	{
	}
#pragma endregion

#pragma region BehaviourComponent
    template<>
	void Scene::OnComponentAdded<BehaviourComponent>(entt::entity e)
	{        
        Entity entity = { e, this };
        auto& bc = entity.GetComponent<BehaviourComponent>();

        if (bc.Instance)
        {
            bc.Instance->m_Entity = Entity{ entity, this };
            bc.Instance->OnCreate();
        }
	}
    template<>
	void Scene::OnComponentRemoved<BehaviourComponent>(entt::entity e)
	{
        Entity entity = { e, this };
        auto& bc = entity.GetComponent<BehaviourComponent>();

        if (bc.Instance)
        {
            bc.Instance->OnDestroy();
            m_BehaviourCleanups.push_back(bc.Instance);
        }
	}
#pragma endregion

#pragma endregion

    Scene::Scene(/* args */)
    {
        // TODO: create some MACRO to register a type youknowwhamisayin

        // Physics
        m_Registry.on_construct<RigidBodyComponent>().connect<&Scene::OnComponentAdded<RigidBodyComponent>>(this);
        m_Registry.on_destroy<RigidBodyComponent>().connect<&Scene::OnComponentRemoved<RigidBodyComponent>>(this);

        m_Registry.on_construct<BoxColliderComponent>().connect<&Scene::OnComponentAdded<BoxColliderComponent>>(this);
        m_Registry.on_destroy<BoxColliderComponent>().connect<&Scene::OnComponentRemoved<BoxColliderComponent>>(this);

        m_Registry.on_construct<CircleColliderComponent>().connect<&Scene::OnComponentAdded<CircleColliderComponent>>(this);
        m_Registry.on_destroy<CircleColliderComponent>().connect<&Scene::OnComponentRemoved<CircleColliderComponent>>(this);

        // Behaviour
        m_Registry.on_construct<BehaviourComponent>().connect<&Scene::OnComponentAdded<BehaviourComponent>>(this);
        m_Registry.on_destroy<BehaviourComponent>().connect<&Scene::OnComponentRemoved<BehaviourComponent>>(this);
    }

    Scene::~Scene()
    {
    }

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { m_Registry.create(), this };
        entity.AddComponent<TransformComponent>();

        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Unnamed Entity" : name;

        // TODO: should create relation component here :)

        return entity;
    }

    void Scene::DestroyEntity(Entity entity)
    {
        m_Registry.destroy(entity);
    }

	void Scene::OnRuntimeStart()
    {
        m_PhysicsWorld = new b2World({ 0.f, 0.f });
        m_PhysicsWorld->SetContactListener(&m_ContactListener);
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
                if (!sc.Instance)
                {
                    sc.Instance = sc.InstantiateScript();
                    sc.Instance->m_Entity = Entity{ entity, this };
                    sc.Instance->OnCreate();
                }
                
                sc.Instance->OnUpdate(ts);
            });

            m_Registry.view<BehaviourComponent>().each([=](auto entity, auto& bc)
            {
                if (bc.Instance)
                {
                    bc.Instance->OnUpdate(ts);
                }
            });
        }

        // Clean up scripts
        {
            // Could use a reverse iterator for performance
            if (m_BehaviourCleanups.size() > 0)
            {
                for (int i = 0; i < m_BehaviourCleanups.size(); i++)
                {
                    delete m_BehaviourCleanups[i];
                    m_BehaviourCleanups[i] = nullptr;
                }
                m_BehaviourCleanups.clear();
            }
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

                b2Body* body = rbc.RuntimeBody;
                const auto& pos = body->GetPosition();
                tc.Translation.x = pos.x;
                tc.Translation.z = pos.y;

                if (rbc.OwnRotation)
                {
                    tc.Rotation.y = glm::degrees(body->GetAngle());
                }
            }
        }

        // Rendering
        {
#ifndef AX_HEADLESS
            //Raylib::BeginDrawing();
            //Raylib::ClearBackground({138, 142, 140, 255});

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

                // AnimatedModel rendering
                {
                    auto view = m_Registry.view<TransformComponent, ModelComponent>();
                    for (auto e : view)
                    {
                        auto [tf, model] = view.get<TransformComponent, ModelComponent>(e);
                        
                        // Update model animation
                        if (model.AnimsCount > 0)
                        {
                            Raylib::ModelAnimation anim = model.Animations[model.AnimIndex];
                            if (anim.frameCount)
                            {
                                model.AnimCurrentFrame = (model.AnimCurrentFrame + 1) % anim.frameCount;
                                Raylib::UpdateModelAnimation(model.Model, anim, model.AnimCurrentFrame);
                            }
                            //model.AnimCurrentFrame = (model.AnimCurrentFrame + 1) % model.Animations[model.AnimIndex].frameCount;
                            //Raylib::UpdateModelAnimation(model.Model, model.Animations[model.AnimIndex], model.AnimCurrentFrame);
                        }

                        Raylib::DrawModelEx(model.Model,
                            { tf.Translation.x, tf.Translation.y, tf.Translation.z },
                            {0.f, 1.0f, 0.f}, tf.Rotation.y,
                            { tf.Scale.x, tf.Scale.y, tf.Scale.z },
                            //{ 0.01f, 0.01f, 0.01f }, // TEMPORARY
                            Raylib::WHITE);
                    }
                }

                // StaticModel rendering
                {
                }

                // Temporary?
                if (Raylib::IsKeyPressed(Raylib::KEY_F8))
                {
                    s_DebugRender = !s_DebugRender;
                }

                if (s_DebugRender)
                {
                    // Debug BoxCollider
                    {
                        auto view = m_Registry.view<TransformComponent, RigidBodyComponent, BoxColliderComponent>();
                        for (auto e : view)
                        {
                            auto [tf, rb, box] = view.get<TransformComponent, RigidBodyComponent, BoxColliderComponent>(e);

                            Raylib::rlPushMatrix();
                            Raylib::rlTranslatef(tf.Translation.x, tf.Translation.y + 1.0f, tf.Translation.z);
                            Raylib::rlRotatef(glm::degrees(rb.RuntimeBody->GetAngle()), 0, 1, 0);
                            Raylib::DrawCubeWiresV({  0.f, 0.f, 0.f }, { box.Size.x * 2, 2.0f, box.Size.y * 2 }, {255, 255, 255, 255});
                            Raylib::rlPopMatrix();
                        }
                    }
                    // Debug CircleCollider
                    {
                        auto view = m_Registry.view<TransformComponent, CircleColliderComponent>();
                        for (auto e : view)
                        {
                            auto [tf, circ] = view.get<TransformComponent, CircleColliderComponent>(e);

                            Raylib::DrawCylinderWires({tf.Translation.x, 0.f, tf.Translation.z}, circ.Radius, circ.Radius, 2.f, 15, {255, 255, 255, 255});
                        }
                    }
                }
                Raylib::EndMode3D();
            }
            else
            {
                //AX_CORE_WARN("There is no camera present in the scene!");
            }
			//Raylib::EndDrawing();
        }
#endif // AX_HEADLESS
	}

}