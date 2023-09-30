#pragma once
#include "entt/entt.hpp"
#include "Scene.h"

namespace Apex {

    // TODO: should remove Component postfix from methods
    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);
        Entity(const Entity& other) = default;

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            AX_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
            return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
        }

        template<typename T>
        T& GetComponent()
        {
            AX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
            return m_Scene->m_Registry.get<T>(m_Handle);
        }

        template<typename T>
        void RemoveComponent()
        {
            AX_CORE_ASSERT(HasComponent<T>(), "Entity doesn't have component!");
            m_Scene->m_Registry.remove<T>(m_Handle);
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Scene->m_Registry.any_of<T>(m_Handle);
        }

        operator bool() const { return m_Handle != entt::null; }

    private:
        entt::entity m_Handle = entt::null;
        Scene* m_Scene;
        // SHOULD BE WEAK_REF or Ref<Scene>
    };

}
