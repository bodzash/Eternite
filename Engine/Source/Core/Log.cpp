#include "axpch.hpp"
#include "Log.hpp"
#include "spdlog/sinks/stdout_sinks.h"

namespace Apex
{

  std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
  std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

  void Log::Init()
  {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("RUNTIME");
    s_ClientLogger->set_level(spdlog::level::trace);
  }

}