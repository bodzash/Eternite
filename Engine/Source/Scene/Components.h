#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "NativeScript.h"

// Fwd decl
class b2Body;
class b2Fixture;

namespace Apex {

    struct CHierarchy
    {
        entt::entity Parent{entt::null};
        //std::vector<entt::entity> Children;
        //std::unordered_map<std::string, entt::entity> Children;
    };

    struct CTag
    {
        std::string Tag = "";

        CTag() = default;
        CTag(const CTag&) = default;
        CTag(const std::string& tag)
            : Tag(tag) {}
    };
    
    struct CTransform
    {
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		CTransform() = default;
		CTransform(const CTransform&) = default;
		CTransform(const glm::vec3& translation)
			: Translation(translation) {}
    };

    /*
    OLD SHIT
    struct ScriptComponent
    {
        NativeScript* Instance = nullptr;

        NativeScript*(*InstantiateScript)();
        void(*DestroyScript)(ScriptComponent*);

        template<typename T>
        void Bind()
        {
            InstantiateScript = []() { return static_cast<NativeScript*>(new T()); };
            DestroyScript = [](ScriptComponent* sc) { delete sc->Instance; sc->Instance = nullptr; };
        }
    };*/

    struct CScript
    {
        NativeScript* Instance = nullptr;

        CScript() = delete;
        CScript(NativeScript* script) { Instance = script; }

        /*
        template<typename T>
        void Bind()
        {
            Instance = new T();
        }
        */

        template<typename T>
        T& As()
        {
            return *static_cast<T*>(Instance);
        }

        template<typename T>
        bool Is()
        {
            return dynamic_cast<T*>(Instance);
        }
    };

    // TODO: create implicit constructors and hide Runtime_xxx stuff make Scene a friend
    struct CRigidBody
    {
        // NOTE: this lines up with b2BodyType enum
        enum class BodyType { Static = 0, Kinematic, Dynamic };

        // TODO: should remove all member variables, and use getters setter in this case

        // Body def (variables only read when created)
        BodyType Type = BodyType::Dynamic;
        float LinearDamping = 10.f;
        bool FixedRotation = false;

        // Does the physics "own" the y rotation
        bool OwnRotation = true;

        // Runtime storage
        b2Body* RuntimeBody = nullptr;

        CRigidBody() = default;
        CRigidBody(const CRigidBody&) = default;

        void SetTransform(glm::vec2 position, float rotation);
        void SetPosition(glm::vec2 position);
        void SetRotation(float rotation);

        // If enabled pyhsics system wont rotate it when colliding
        void SetFixedRotation(bool enable);

        void ApplyForce(glm::vec2 force);
    };

    // TODO: create implicit constructors and hide Runtime_xxx stuff make Scene a friend
    struct CBoxCollider
    {
        glm::vec2 Offset = { 0.f, 0.f };
        glm::vec2 Size = { 0.5f, 0.5f };

        float Density = 1.0f;
        float Friction = 0.5f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.1f;

        void SetFilterCategory(uint16_t category);
        void SetFilterMask(uint16_t mask);

        // Runtime storage
        b2Fixture* RuntimeFixture = nullptr;

        CBoxCollider() = default;
        CBoxCollider(const CBoxCollider&) = default;
    };

    // TODO: create implicit constructors and hide Runtime_xxx stuff make Scene a friend
    struct CCircleCollider
    {
        glm::vec2 Offset = { 0.f, 0.f };
        float Radius = 0.5f;

        float Density = 1.0f;
        float Friction = 0.5f;
        float Restitution = 0.0f;
        float RestitutionThreshold = 0.2f;

        void SetFilterCategory(uint16_t category);
        void SetFilterMask(uint16_t mask);

        // Runtime storage
        b2Fixture* RuntimeFixture = nullptr;

        CCircleCollider() = default;
        CCircleCollider(const CCircleCollider&) = default;
    };

    // TODO: implement later
    struct CPolygonCollider
    {
        CPolygonCollider() = default;
        CPolygonCollider(const CPolygonCollider&) = default;
    };

}