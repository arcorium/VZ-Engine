#pragma once

#include "spdlog/spdlog.h"
#include "Core.h"

namespace vz {

	class VZ_API Log
	{
	private:
		static std::shared_ptr<spdlog::logger> m_coreLogger;
		static std::shared_ptr<spdlog::logger> m_clientLogger;
	public:

		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_coreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_clientLogger; }

	};

}


#ifdef VZ_DEBUG
	// Core Logger
	#define VZ_CORE_TRACE(...)		::vz::Log::GetCoreLogger()->trace(__VA_ARGS__)		// Prepended double colon means that the namespace start from global namespace
	#define VZ_CORE_INFO(...)		::vz::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define VZ_CORE_WARN(...)		::vz::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define VZ_CORE_ERROR(...)		::vz::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define VZ_CORE_CRITICAL(...)	::vz::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client Logger
	#define VZ_TRACE(...)		::vz::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define VZ_INFO(...)		::vz::Log::GetClientLogger()->info(__VA_ARGS__)
	#define VZ_WARN(...)		::vz::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define VZ_ERROR(...)		::vz::Log::GetClientLogger()->error(__VA_ARGS__)
	#define VZ_CRITICAL(...)	::vz::Log::GetClientLogger()->critical(__VA_ARGS__)
#elif defined VZ_RELEASE || VZ_DIST
	// When on release stage the log will not be activated
	#define VZ_CORE_TRACE(...)
	#define VZ_CORE_INFO(...)
	#define VZ_CORE_WARN(...)
	#define VZ_CORE_ERROR(...)
	#define VZ_CORE_CRITICAL(...)

	#define VZ_TRACE(...)	
	#define VZ_INFO(...)	
	#define VZ_WARN(...)	
	#define VZ_ERROR(...)	
	#define VZ_CRITICAL(...)
#endif


