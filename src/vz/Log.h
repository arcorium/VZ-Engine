#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"

namespace vz {

	/**
	 * \brief static class for logging
	 */
	class VZ_API Log
	{
	public:

		static void Init();

		/**
		 * \brief Get core logger
		 * \return pointer reference of core logger
		 */
		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_coreLogger; }

		/**
		 * \brief Get client logger
		 * \return pointer reference of client logger
		 */
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> m_coreLogger;
		static std::shared_ptr<spdlog::logger> m_clientLogger;
	};

}


#ifdef VZ_DEBUG
	// Core Logger
	#define VZ_CORE_TRACE(fmt, ...)		::vz::Log::GetCoreLogger()->trace(fmt, __VA_ARGS__)		// Prepended double colon means that the namespace start from global namespace
	#define VZ_CORE_INFO(fmt, ...)		::vz::Log::GetCoreLogger()->info(fmt, __VA_ARGS__)		// Ellipsis used for variable will be passed on first argument
	#define VZ_CORE_WARN(fmt, ...)		::vz::Log::GetCoreLogger()->warn(fmt, __VA_ARGS__)
	#define VZ_CORE_ERROR(fmt, ...)		::vz::Log::GetCoreLogger()->error(fmt, __VA_ARGS__)
	#define VZ_CORE_CRITICAL(fmt, ...)	::vz::Log::GetCoreLogger()->critical(fmt, __VA_ARGS__)

	// Client Logger
	#define VZ_TRACE(fmt, ...)		::vz::Log::GetClientLogger()->trace(fmt, __VA_ARGS__)
	#define VZ_INFO(fmt, ...)		::vz::Log::GetClientLogger()->info(fmt, __VA_ARGS__)
	#define VZ_WARN(fmt, ...)		::vz::Log::GetClientLogger()->warn(fmt, __VA_ARGS__)
	#define VZ_ERROR(fmt, ...)		::vz::Log::GetClientLogger()->error(fmt, __VA_ARGS__)
	#define VZ_CRITICAL(fmt, ...)	::vz::Log::GetClientLogger()->critical(fmt, __VA_ARGS__)
#elif defined VZ_RELEASE || VZ_DIST
	// When on release stage the log will not be activated
	#define VZ_CORE_TRACE(fmt, ...)
	#define VZ_CORE_INFO(fmt, ...)
	#define VZ_CORE_WARN(fmt, ...)
	#define VZ_CORE_ERROR(fmt, ...)
	#define VZ_CORE_CRITICAL(fmt, ...)

	#define VZ_TRACE(fmt, ...)	
	#define VZ_INFO(fmt, ...)	
	#define VZ_WARN(fmt, ...)	
	#define VZ_ERROR(fmt, ...)	
	#define VZ_CRITICAL(fmt, ...)
#endif


