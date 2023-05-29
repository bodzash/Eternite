#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Core/Log.hpp"
//#include "Apex/Debug/Instrumentor.hpp"

// Platform specific
#ifdef AX_PLATFORM_WINDOWS
  #include <Windows.h>
#endif