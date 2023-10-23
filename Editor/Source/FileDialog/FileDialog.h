#pragma once
#include <string>
#include <Core/Application.h>

namespace Apex {

    class FileDialog
    {
    public:
        static std::string OpenFile(const char* filter);
        static std::string SaveFile(const char* filter);
    };

}