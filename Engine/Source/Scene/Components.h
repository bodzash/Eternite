#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "NativeBehaviour.h"

// TODO: put components into their own files probably

namespace Apex {

    struct RelationComponent
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

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

            // Order is important! T->R->S
			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
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

}