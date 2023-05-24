#include "axpch.hpp"
#include "Entity.hpp"

namespace Apex
{

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_Handle(handle), m_Scene(scene) {}

}