#include "Components.h"
#include "Math/Math.h"
#include <box2d/b2_body.h>

namespace Apex {

    void RigidBodyComponent::SetTransform(glm::vec2 position, float rotation)
    {
        RuntimeBody->SetTransform({position.x, position.y}, Math::DegToRad(rotation));
    }

    void RigidBodyComponent::SetPosition(glm::vec2 position)
    {
        RuntimeBody->SetTransform({position.x, position.y}, RuntimeBody->GetAngle());
    }

    void RigidBodyComponent::SetRotation(float rotation)
    {
        RuntimeBody->SetTransform(RuntimeBody->GetPosition(), Math::DegToRad(rotation));
    }
}