#include "ContactListener2D.h"
#include <entt/entt.hpp>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_contact.h>
#include "Scene/Entity.h"
#include "Scene/Components.h"

namespace Apex {

    ContactListener2D::ContactListener2D(Scene* scene)
    {
        m_Scene = scene;
    }

    void ContactListener2D::BeginContact(b2Contact* contact)
    {
        entt::entity entityA = static_cast<entt::entity>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        entt::entity entityB = static_cast<entt::entity>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        Entity a = { entityA, m_Scene };
        Entity b = { entityB, m_Scene };

        if (a.HasComponent<BehaviourComponent>())
        {
            auto& nb = a.GetComponent<BehaviourComponent>();
            nb.Instance->OnCollisionEnter(b);
        }

        if (b.HasComponent<BehaviourComponent>())
        {
            auto& nb = b.GetComponent<BehaviourComponent>();
            nb.Instance->OnCollisionEnter(a);
        }
    }

    void ContactListener2D::EndContact(b2Contact* contact)
    {
        entt::entity entityA = static_cast<entt::entity>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        entt::entity entityB = static_cast<entt::entity>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        Entity a = { entityA, m_Scene };
        Entity b = { entityB, m_Scene };

        if (a.HasComponent<BehaviourComponent>())
        {
            auto& nb = a.GetComponent<BehaviourComponent>();
            nb.Instance->OnCollisionLeave(b);
        }

        if (b.HasComponent<BehaviourComponent>())
        {
            auto& nb = b.GetComponent<BehaviourComponent>();
            nb.Instance->OnCollisionLeave(a);
        }
    }

}