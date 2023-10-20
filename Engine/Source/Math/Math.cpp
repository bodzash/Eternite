#include "Math.h"

namespace Apex {

    namespace Math {

        float RadToDeg(float radian)
        {
            return radian * (180.0f / 3.14159265359f);
        }

        float DegToRad(float degree)
        {
            return degree * (3.14159265359f / 180.0f);
        }

    }

}