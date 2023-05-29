#pragma once
#include "entt/entt.hpp"
#include "Core/Timestep.hpp"

namespace Apex
{

    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = "");

        void OnUpdate(Timestep ts);

    private:
        entt::registry m_Registry;

        friend class Entity;
    };

}