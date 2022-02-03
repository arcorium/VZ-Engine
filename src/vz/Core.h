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

#elif defined VZ_PLATFROM_UNIX
	#define VZ_API
#else
	#error set define to VZ_PLATFORM_[WIN|UNIX]
#endif

// Set class derived from Application as entry point
#define APP(app)	vz::Application* vz::CreateApp() { return new app();}

#define BIT(x)		1 << x

// Debug Purpose
#ifdef VZ_DEBUG
	#define VZ_DO(pred)	pred
#elif define VZ_RELEASE || VZ_DIST
	#define VZ_DO(pred) 
#endif