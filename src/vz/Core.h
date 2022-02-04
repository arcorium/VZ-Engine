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
#define APP(app)	vz::Application* vz::CreateApp() { return new (app)();}

#define BIT(x)		1 << (x)

// Only executed when it is on debug configuration
#ifdef VZ_DEBUG
	#define VZ_DEBUG_DO(pred)	(pred)
#elif define VZ_RELEASE || VZ_DIST
	#define VZ_DEBUG_DO(pred) 
#endif

// Assert
#ifdef VZ_ASSERT_ENABLED
	#define VZ_ASSERT(condition,...)		if(!condition) VZ_ERROR(__VA_ARGS__); assert(condition)
	#define VZ_CORE_ASSERT(condition,...)	if(!condition) VZ_CORE_ERROR(__VA_ARGS__); assert(condition)
#else
	#define VZ_ASSERT(condition,...)		condition
	#define VZ_CORE_ASSERT(condition,...)	condition
#endif

// Casting

#define INT(x)		static_cast<int>(x)
//#define FLOAT(x)	static_cast<int>(x)
//#define DOUBLE(x)	static_cast<int>(x)
//#define UINT(x)		static_cast<unsigned>(x)