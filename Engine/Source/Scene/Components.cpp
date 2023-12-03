#include "Components.h"
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>

namespace Apex {

#pragma region CRigidBody
    void CRigidBody::SetTransform(glm::vec2 position, float rotation)
    {
        RuntimeBody->SetTransform({position.x, position.y}, glm::radians(rotation));
    }

    void CRigidBody::SetPosition(glm::vec2 position)
    {
        RuntimeBody->SetTransform({position.x, position.y}, RuntimeBody->GetAngle());
    }

    void CRigidBody::SetRotation(float rotation)
    {
        RuntimeBody->SetTransform(RuntimeBody->GetPosition(), glm::radians(rotation));
    }

    void CRigidBody::ApplyForce(glm::vec2 force)
    {
        RuntimeBody->ApplyForceToCenter({ force.x, force.y }, true);
    }

    void CRigidBody::SetFixedRotation(bool enable)
    {
        RuntimeBody->SetFixedRotation(enable);
    }
#pragma endregion

#pragma region CBoxCollider
    void CBoxCollider::SetFilterCategory(uint16_t category)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.categoryBits = category;
        RuntimeFixture->SetFilterData(filter);
    }

    void CBoxCollider::SetFilterMask(uint16_t mask)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.maskBits = mask;
        RuntimeFixture->SetFilterData(filter);
    }
#pragma endregion

#pragma region CCircleCollider
    void CCircleCollider::SetFilterCategory(uint16_t category)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.categoryBits = category;
        RuntimeFixture->SetFilterData(filter);
    }

    void CCircleCollider::SetFilterMask(uint16_t mask)
    {
        b2Filter filter = RuntimeFixture->GetFilterData();
        filter.maskBits = mask;
        RuntimeFixture->SetFilterData(filter);
    }
#pragma endregion
}