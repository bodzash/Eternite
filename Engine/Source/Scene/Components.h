#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "NativeBehaviour.h"

// Fwd decl
class b2Body;
class b2Fixture;

namespace Apex {

    struct HierarchyComponent
    {
        entt::entity Parent{entt::null};
        //std::vector<entt::entity> Children;
        //std::unordered_map<std::string, entt::entity> Children;
    };

    struct GroupComponent
    {
    };

    struct TagComponent
    {
        std::string Tag = "";

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag)
            : Tag(tag) {}
    };
    
    struct TransformComponent
    {
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}
    };

    struct ScriptComponent
    {
        NativeBehaviour* Instance = nullptr;

        NativeBehaviour*(*InstantiateScript)();
        void(*DestroyScript)(ScriptComponent*);

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<NativeBehaviour*>(new T()); };
            DestroyScript = [](ScriptComponent* sc) { delete sc->Instance; sc->Instance = nullptr; };
        }
    };

    struct BehaviourComponent
    {
        NativeBehaviour* Instance = nullptr;

        BehaviourComponent() = delete;
        BehaviourComponent(NativeBehaviour* behaviour) { Instance = behaviour; }

        template<typename G>
        G& As()
        {
            return *static_cast<G*>(Instance);
        }
    };

    // TODO: create implicit constructors and hide Runtime_xxx stuff make Scene a friend
    struct RigidBodyComponent
    {
        // NOTE: this lines up with b2BodyType enum
        enum class BodyType { Static = 0, Kinematic, Dynamic };

        // TODO: should remove all member variables, and use getters setter in this case

        // Body def (variables only read when created)
        BodyType Type = BodyType::Dynamic;
        float LinearDamping = 10.f;
        bool FixedRotation = false;

        // Other def
        bool OwnRotation = true;

        // Runtime storage
        b2Body* RuntimeBody = nullptr;

        RigidBodyComponent() = default;
        RigidBodyComponent(const RigidBodyComponent&) = default;

        void SetTransform(glm::vec2 position, float rotation);
        void SetPosition(glm::vec2 position);
        void SetRotation(float rotation);

        void SetFixedRotation(bool enable);

        void ApplyForce(glm::vec2 force);
    };

    // TODO: create implicit constructors and hide Runtime_xxx stuff make Scene a friend
    struct BoxColliderComponent
    {
        glm::vec2 Offset = { 0.f, 0.f };
        glm::vec2 Size = { 0.5f, 0.5f };

        float Density = 1.0f;
        float Friction = 0.5f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.1f;

        // Runtime storage
        b2Fixture* RuntimeFixture = nullptr;

        BoxColliderComponent() = default;
        BoxColliderComponent(const BoxColliderComponent&) = default;
    };

    // TODO: create implicit constructors and hide Runtime_xxx stuff make Scene a friend
    struct CircleColliderComponent
    {
        glm::vec2 Offset = { 0.f, 0.f };
        float Radius = 0.5f;

        float Density = 1.0f;
        float Friction = 0.5f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.2f;

        // Runtime storage
        b2Fixture* RuntimeFixture = nullptr;

        CircleColliderComponent() = default;
        CircleColliderComponent(const CircleColliderComponent&) = default;
    };

    // TODO: implement but later
    struct PolygonColliderComponent
    {
    };

}