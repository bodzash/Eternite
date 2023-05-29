#include "axpch.hpp"
#include "Scene.hpp"
#include "Scene/Components.hpp"
#include "Scene/Entity.hpp"
#include "glm/glm.hpp"

namespace Apex
{

    // .connect provides these params
    static void OnTransformConstructed(entt::registry& reg, entt::entity ent)
    {

    }

    Scene::Scene(/* args */)
    {
        struct TransformComponent
        {
            glm::mat4 Transform;

            TransformComponent() = default;
            TransformComponent(const TransformComponent&) = default;
            TransformComponent(const glm::mat4& transform)
                : Transform(transform) {}

            operator glm::mat4& () { return Transform; }
            operator const glm::mat4& () const { return Transform; }

            //now .has<T> for entt::registry no more support, replace with all_of or any_of
        };


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
}