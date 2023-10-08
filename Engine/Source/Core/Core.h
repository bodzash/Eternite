#pragma once
#include <memory>

#ifdef AX_ENABLE_ASSERTS
	#define AX_ASSERT(x, ...) { if(!x) { AX_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define AX_CORE_ASSERT(x, ...) { if(!x) { AX_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define AX_ASSERT(x, ...) 
	#define AX_CORE_ASSERT(x, ...) 
#endif

#define BIT(x) (1 << x)

#define AX_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Apex {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	// TODO: implement weakref might need it :D

}