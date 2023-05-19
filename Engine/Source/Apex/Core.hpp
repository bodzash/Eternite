#pragma once

#ifdef AX_PLATFORM_WINDOWS
  #ifdef AX_BUILD_DLL
    #define APEX_API __declspec(dllexport)
  #else
    #define APEX_API __declspec(dllimport)
  #endif
#else
    
#endif

#define BIT(x) (1 << x)