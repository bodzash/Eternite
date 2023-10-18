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
        //std::array<> Children;
        //std::vector<> Children;
        //std::set<> Children;
        //std::unordered_map<std::string, entt::entity> Children;
    };

    struct TagComponent
    {
        std::string Tag;

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

    // TODO: create implicit constructors and hide Runtime_xxx stuff make Scene a friend
    struct RigidBodyComponent
    {
        // NOTE: this lines up with b2BodyType enum
        enum class BodyType { Static = 0, Kinematic, Dynamic };

        BodyType Type = BodyType::Dynamic;
        bool FixedRotation = false;

        // Runtime storage
        b2Body* RuntimeBody = nullptr;

        RigidBodyComponent() = default;
        RigidBodyComponent(const RigidBodyComponent&) = default;

        void SetTransform(glm::vec2 position, float rotation);
        void SetPosition(glm::vec2 position);
        void SetRotation(float rotation);
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

    // TODO: implement
    struct CircleColliderComponent
    {
        glm::vec2 Offset = { 0.f, 0.f };
        float Radius = 1.0f;

        float Density = 1.0f;
        float Friction = 0.5f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.2f;

        // Runtime storage
        void* RuntimeFixture = nullptr;

        CircleColliderComponent() = default;
        CircleColliderComponent(const CircleColliderComponent&) = default;
    };

    // TODO: implement but later
    struct PolygonColliderComponent
    {
        glm::vec2 Offset = { 0.f, 0.f };
        /*
            Needs vertices and some other shit
        */
        float Density = 1.0f;
        float Friction = 0.5f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.2f;

        // Runtime storage
        void* RuntimeFixture = nullptr;

        PolygonColliderComponent() = default;
        PolygonColliderComponent(const PolygonColliderComponent&) = default;
    };

}