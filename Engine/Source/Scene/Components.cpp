#include "Components.h"
#include <box2d/b2_body.h>

namespace Apex {

    void RigidBodyComponent::SetTransform(glm::vec2 position, float rotation)
    {
        RuntimeBody->SetTransform({position.x, position.y}, glm::radians(rotation));
    }

    void RigidBodyComponent::SetPosition(glm::vec2 position)
    {
        RuntimeBody->SetTransform({position.x, position.y}, RuntimeBody->GetAngle());
    }

    void RigidBodyComponent::SetRotation(float rotation)
    {
        RuntimeBody->SetTransform(RuntimeBody->GetPosition(), glm::radians(rotation));
    }

    void RigidBodyComponent::ApplyForce(glm::vec2 force)
    {
        RuntimeBody->ApplyForceToCenter({ force.x, force.y }, true);
    }
}