#pragma once
#include "Core/Core.h"
#include "Entity.h"

namespace Apex {

    class NativeScript
    {
    public:
        virtual ~NativeScript() {}

        template<typename T, typename... Args>
        T& Add(Args&&... args)
        {
            return m_Entity.Add<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        T& Get()
        {
            return m_Entity.Get<T>();
        }

        template<typename T>
        void Remove()
        {
            m_Entity.Remove<T>();
        }

        template<typename T>
        bool Has()
        {
            return m_Entity.Has<T>();
        }

        Entity GetSelfEntity()
        {
            return m_Entity;
        }

        Entity CreateEntity(const std::string& name = "")
        {
            return m_Entity.m_Scene->CreateEntity(name);
        }

        void DestroyEntity(Entity entity)
        {
            entity.Add<MarkedRemoveInternal>();
        }

        // Get/HasParent()
        // Get/HasChildren
        // Get/HasChildByName(name)

    protected:
        virtual void OnCreate() {}
        virtual void OnDestroy() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnCollisionEnter(Entity other) {}
        virtual void OnCollisionLeave(Entity other) {}

    private:
        Entity m_Entity;
        friend class Scene;
        friend class ContactListener2D;
    };

}