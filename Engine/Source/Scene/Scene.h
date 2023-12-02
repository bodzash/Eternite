#pragma once
#include <entt/entt.hpp>
#include "Core/Timestep.h"
#include "Physics/ContactListener2D.h"

// Fwd decl
class b2World;

namespace Apex {

    // Fwd decl
    class Entity;
    class NativeBehaviour;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = "");
        void DestroyEntity(Entity entity);
        // create entity with uuid
        // Find entity by id
        // find entity by name
        // get primary camera

        void OnRuntimeStart();
        void OnRuntimeStop();
        void OnPhysicsStart();
        void OnPhysicsStop();
        void OnUpdate(Timestep ts);

    private:
        entt::registry m_Registry;
        std::vector<NativeBehaviour*> m_BehaviourCleanups;
        b2World* m_PhysicsWorld = nullptr;
        ContactListener2D m_ContactListener{ this };
        //std::unordered_map<UUID, entt::entity> m_EntityMap;

        template<typename T>
		void OnComponentAdded(entt::entity e);
        template<typename T>
		void OnComponentRemoved(entt::entity e);

        void RegisterComponentCallbacks();

        friend class Entity;
        friend class HierarchyPanel;
        friend class SceneSerializer;
    };

    struct MarkedRemoveInternal
    {
        // Need to have some data here... :D
        bool ShouldDelete = true;
    };

}