#include "Components.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace Apex {

#pragma region RigidBodyComponent
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

    void RigidBodyComponent::SetFixedRotation(bool enable)
    {
        RuntimeBody->SetFixedRotation(enable);
    }
#pragma endregion

#pragma region BoxColliderComponent
    void BoxColliderComponent::SetFilterCategory(uint16_t category)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.categoryBits = category;
        RuntimeFixture->SetFilterData(filter);
    }

    void BoxColliderComponent::SetFilterMask(uint16_t mask)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.maskBits = mask;
        RuntimeFixture->SetFilterData(filter);
    }
#pragma endregion

#pragma region CircleColliderComponent
    void CircleColliderComponent::SetFilterCategory(uint16_t category)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.categoryBits = category;
        RuntimeFixture->SetFilterData(filter);
    }

    void CircleColliderComponent::SetFilterMask(uint16_t mask)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.maskBits = mask;
        RuntimeFixture->SetFilterData(filter);
    }
#pragma endregion
}