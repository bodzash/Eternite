#pragma once
#include "Core/Core.h"
#include <box2d/b2_world_callbacks.h>

namespace Apex {

    // Fwd decl
    class Scene;

    class ContactListener2D : public b2ContactListener
    {
    public:
        ContactListener2D(Scene* scene);
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);

    private:
        // TODO: could be a smart ptr or something
        Scene* m_Scene = nullptr;
    };

}