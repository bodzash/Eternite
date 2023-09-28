#include "axpch.h"
#include "Entity.h"

namespace Apex
{

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_Handle(handle), m_Scene(scene) {}

}