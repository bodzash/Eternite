#pragma once

namespace Apex {

    using MouseCode = int;

    namespace Mouse {

        // From raylib.h
        enum : MouseCode
        {
            Left = 0,
            Right = 1,
            Middle = 2,
            Side = 3,
            Extra = 4,
            Forward = 5,
            Back = 6
        };

    }
}