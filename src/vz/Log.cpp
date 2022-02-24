#include "vzpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace vz
{
	// static member declaration goes here (in header file is just like prototype, except the static member is also declared in there)
	std::shared_ptr<spdlog::logger> Log::m_coreLogger;
	std::shared_ptr<spdlog::logger> Log::m_clientLogger;

	void Log::Init()
	{
		// Init all log object
		m_coreLogger = spdlog::stdout_color_mt("VZ");
		m_clientLogger = spdlog::stdout_color_mt("APP");

		// Set format
		m_coreLogger->set_pattern("[%T] - %^[%l]%$ -- %n -> %v");
		m_clientLogger->set_pattern("[%T] - %^[%l]%$ -- %n -> %v");
	}
}
