#pragma once
#include "glm/glm.hpp"

// TODO: put components into their own files

namespace Apex {

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
        glm::mat4 Transform{ 1.f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::mat4& transform)
            : Transform(transform) {}

        operator glm::mat4& () { return Transform; }
        operator const glm::mat4& () const { return Transform; }
    };

    struct MeshComponent
    {
        // TODO: do not use strings, use a smart pointer (ref or scope) :D
        std::string Name;

        MeshComponent() = default;
        MeshComponent(const MeshComponent&) = default;
    };

}