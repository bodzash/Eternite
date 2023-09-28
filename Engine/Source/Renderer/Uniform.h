#pragma once
#include <string>
#include "HandleImpl.h"

// TODO: same thing with HandleImpl.h

namespace Apex {

    class Uniform : public HandleImpl<uniform_handle>
    {
    public:
        Uniform() = default;
        Uniform(const std::string& _name, uniform_type _type, std::uint16_t _num = 1);
        Uniform(handle_type_t _handle);

        /// Uniform info
        uniform_info info;
    };

}