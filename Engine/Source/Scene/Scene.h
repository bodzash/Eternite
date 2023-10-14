#pragma once
#include "entt/entt.hpp"
#include "Core/Timestep.h"

// Fwd decl
class b2World;

namespace Apex {

    // Fwd decl
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = "");
        //void DestroyEntity(Entity entity);
        // create entity with uuid
        // Find entity by id
        // find entity by name
        // get primary camera

        void OnRuntimeStart();
        void OnRuntimeStop();
        void OnPhysicsStart();
        void OnPhysicsStop();
        void OnUpdate(Timestep ts);

        template<typename T>
		void OnComponentAdded(Entity entity, T& component);

    private:
        entt::registry m_Registry;
        b2World* m_PhysicsWorld = nullptr;
        //std::unordered_map<UUID, entt::entity> m_EntityMap;
        //void OnScriptCreated(entt::registry& reg, entt::entity ent);

        friend class Entity;
    };

}