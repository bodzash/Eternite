#pragma once
#include <memory>
#include "Core.hpp"
#include "spdlog/spdlog.h"

namespace Apex
{

  class APEX_API Log
  {
  public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

  private:
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;
  };

}

// When we are building release mode we need to set them to nothing
// Core log macros
#define AX_CORE_TRACE(...) ::Apex::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define AX_CORE_INFO(...)  ::Apex::Log::GetCoreLogger()->info(__VA_ARGS__)
#define AX_CORE_WARN(...)  ::Apex::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define AX_CORE_ERROR(...) ::Apex::Log::GetCoreLogger()->error(__VA_ARGS__)
#define AX_CORE_FATAL(...) ::Apex::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define AX_TRACE(...) ::Apex::Log::GetClientLogger()->trace(__VA_ARGS__)
#define AX_INFO(...)  ::Apex::Log::GetClientLogger()->info(__VA_ARGS__)
#define AX_WARN(...)  ::Apex::Log::GetClientLogger()->warn(__VA_ARGS__)
#define AX_ERROR(...) ::Apex::Log::GetClientLogger()->error(__VA_ARGS__)
#define AX_FATAL(...) ::Apex::Log::GetClientLogger()->fatal(__VA_ARGS__)

/*
  If dist build, define them as nothing
  #define EN_TRACE(...) 
*/