#pragma once
#include "bgfx/bgfx.h"

// TODO: could be useful but should be deleted

namespace Apex {

    template<typename T>
    class HandleImpl
    {
    public:
        using HandleType_t = T;
        using BaseType_t = HandleImpl<T>;

        ~HandleImpl()
        {
            Dispose();
        }

        void Dispose()
        {
            if(IsValid())
            {
                bgfx::destroy(m_Handle);
            }

            m_Handle = InvalidHandle();
        }

        bool IsValid() const
        {
            return bgfx::isValid(m_Handle);
        }

        T NativeHandle() const
        {
            return m_Handle;
        }

        static T InvalidHandle()
        {
            T invalid = { bgfx::kInvalidHandle };
            return invalid;
        }

    protected:
        T m_Handle = InvalidHandle();
    };
}