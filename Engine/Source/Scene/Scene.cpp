#include "axpch.h"
#include "Scene.h"
#include "Scene/Components.h"
#include "Scene/Entity.h"
#include "glm/glm.hpp"

//now .has<T> for entt::registry no more support, replace with all_of or any_of

namespace Apex {

    // .connect provides these params
    static void OnTransformConstructed(entt::registry& reg, entt::entity ent)
    {
        AX_WARN("TransformComponent Constructed!");
    }

    Scene::Scene(/* args */)
    {
        // Set up component life cycle methods
        m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstructed>();
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

        return { m_Registry.create(), this };
    }

    void Scene::OnUpdate(Timestep ts)
    {

    }

/*
#pragma region ComponentLifeCycles
#pragma endregion

#pragma region xyzSystem
#pragma endregion
*/

}