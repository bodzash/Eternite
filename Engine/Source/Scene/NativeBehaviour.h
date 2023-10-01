#pragma once
#include "Core/Core.h"
#include "Entity.h"

namespace Apex {

    class NativeBehaviour
    {
    public:
        virtual ~NativeBehaviour() {}

        template<typename T, typename... Args>
        T& AddComponent(Args&&... args)
        {
            return m_Entity.AddComponent<T>(std::forward<Args>(args)...);
            //return m_Entity.AddComponent<T>(args);
        }

        template<typename T>
        T& GetComponent()
        {
            return m_Entity.GetComponent<T>();
        }

        template<typename T>
        void RemoveComponent()
        {
            m_Entity.RemoveComponent<T>();
        }

        template<typename T>
        bool HasComponent()
        {
            return m_Entity.HasComponent<T>();
        }

        // Get/HasParent()
        // Get/HasChildren
        // Get/HasChildByName(name)

    protected:
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate(Timestep ts) {}
        //virtual void OnCollision(Entity other) {} should use the ones bellow
        //virtual void OnCollisionEnter(Entity other) {}
        //virtual void OnCollisionLeave(Entity other) {}

    private:
        Entity m_Entity;
        friend class Scene;
        //friend static void Scene::OnScriptCreated(entt::registry& reg, entt::entity ent);
    };

}