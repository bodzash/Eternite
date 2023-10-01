#include "axpch.h"
#include "Scene.h"
#include "Scene/Components.h"
#include "Scene/Entity.h"
#include <glm/glm.hpp>

//now .has<T> for entt::registry no more support, replace with all_of or any_of

namespace Apex {

    static void OnTransformCreated(entt::registry& reg, entt::entity ent)
    {
        //AX_INFO("TransformComponent Constructed!");
    }

    static void OnScriptCreated(entt::registry& reg, entt::entity ent)
    {
        /*
        auto& sc = reg.get<ScriptComponent>(ent);
        sc.Instance = sc.InstantiateScript();
        sc.Instance->m_Entity = Entity{ ent, this };
        sc.Instance->OnCreate();
        */
    }

    Scene::Scene(/* args */)
    {
        // Set up component life cycle methods
        // TODO: make a wrapper around these
        //m_Registry.on_construct<TransformComponent>().connect<&OnComponentAdded<TransformComponent>>();
        m_Registry.on_construct<TransformComponent>().connect<OnTransformCreated>();
        m_Registry.on_construct<ScriptComponent>().connect<OnScriptCreated>();
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

        // should create relation component here :)

        return entity;
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

        }

        // Rendering
        {

        }
    }

#pragma region ComponentLifeCycles

    template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(sizeof(T) == 0);
	}

    template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
        AX_WARN("TransformComponent Constructed!");
	}

#pragma endregion

/*
#pragma region ComponentLifeCycles
#pragma endregion

#pragma region xyzSystem
#pragma endregion
*/

}