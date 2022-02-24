#pragma once

#ifdef VZ_PLATFORM_WIN
	// Building library as shared or static
	#ifdef VZ_BUILD
		#ifdef VZ_BUILD_SHARED
			#define VZ_API	__declspec(dllexport)
		#else
			#define VZ_API
		#endif

	#else
	// Make executable with static or shared library
		#if VZ_STATIC
			#define VZ_API
		#else
			#define VZ_API	__declspec(dllimport)
		#endif
	#endif

#elif defined VZ_PLATFORM_UNIX
	#define VZ_API
#else
	#error set define to VZ_PLATFORM_[WIN|UNIX]
#endif

// Set class derived from Application as entry point
#define APP(app)	::vz::Application* ::vz::CreateApp() { return new (app)();}

#define BIT(x)		1 << (x)

// Only executed when it is on debug configuration
#ifdef VZ_DEBUG
	#define VZ_DEBUG_DO(pred)	pred
#elif define VZ_RELEASE || VZ_DIST
	#define VZ_DEBUG_DO(pred) 
#endif

// Assert
#ifdef VZ_ASSERT_ENABLED
	#define VZ_ASSERT(condition,...)			assert(condition && __VA_ARGS__)
	#define VZ_STATIC_ASSERT(condition, ...)	static_assert(condition && __VA_ARGS__)
	#define VZ_CORE_ASSERT(condition,...)		if(!condition) VZ_CORE_ERROR(__VA_ARGS__); assert(condition)
#else
	#define VZ_ASSERT(condition,...)			condition
	#define VZ_STATIC_ASSERT(condition, ...)	condition
	#define VZ_CORE_ASSERT(condition,...)		condition
#endif

// Casting

#define INT(x)		static_cast<int>(x)
#define FLOAT(x)	static_cast<float>(x)
#define DOUBLE(x)	static_cast<double>(x)
//#define UINT(x)		static_cast<unsigned>(x)

#define VZ_ARRAY_LENGTH(arr)	(sizeof(arr) / sizeof(arr[0]))	
#define VZ_SAFE_DELETE(ptr)		if (ptr) delete ptr; ptr = nullptr

// Because the parameter is auto the decltype will deduce the argument type
#define VZ_BIND_EVENT_VOID(fn)		[this](auto&& args){ fn(std::forward<decltype(args)>(args));}
// Like above but with explicit template (auto is 'implicit template, "MAYBE")
#define VZ_BIND_EVENT_BOOL(fn)		[this]<typename T>(T&& args){ return fn(std::forward<T>(args));}