#include "Utils.h"

namespace Raylib {
    #include <raymath.h>
}

namespace Apex {

    glm::vec3 GetScreenFloorRay(glm::vec2 pos, Raylib::Camera3D cam)
    {
        Raylib::Ray raycast = Raylib::GetMouseRay({ pos.x, pos.y }, cam);
        Raylib::Vector3 plane = { 0.f, 1.f, 0.f };
        Raylib::Vector3 out = { 0.f, 0.f, 0.f };

        // Check if paralell
        float dot = Raylib::Vector3DotProduct(raycast.direction, plane);
        float t = -(plane.x * raycast.position.x + plane.y * raycast.position.y + plane.z * raycast.position.z) / dot;

        out.x = raycast.position.x + raycast.direction.x * t;
        out.y = raycast.position.y + raycast.direction.y * t;
        out.z = raycast.position.z + raycast.direction.z * t;

        return { out.x, out.y, out .z };
    }

    float PointDirection(glm::vec3 from, glm::vec3 to)
    {
        float ang = atan2((-to.z) - (-from.z), to.x - from.x) * (180.0 / 3.14);
        //if (ang < 0) ang += 6.28;
        if (ang < 0) ang += 360.f;

        return ang;
    }
}