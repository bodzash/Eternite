#pragma once
#include <glm/glm.hpp>

namespace Raylib {
    #include <raylib.h>
}

namespace Apex {

    glm::vec3 GetScreenFloorRay(glm::vec2 pos, Raylib::Camera cam);
    float PointDirection(glm::vec3 from, glm::vec3 to);

}