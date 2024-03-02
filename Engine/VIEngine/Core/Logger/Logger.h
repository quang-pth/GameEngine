#pragma once

#include<spdlog/fmt/ostr.h>
#include<spdlog/sinks/stdout_color_sinks.h>
#include"pch.h"

namespace VIEngine {
	class VI_API Logger {
	public:
		static void Init();
		static VI_FORCE_INLINE Shared<spdlog::logger> GetCoreLogger() { return sCoreLogger; }
		static VI_FORCE_INLINE Shared<spdlog::logger> GetClientLogger() { return sClientLogger; }
	private:
		static Shared<spdlog::logger> sCoreLogger;
		static Shared<spdlog::logger> sClientLogger;
	};
}

#define LOG_WITH_DETAILS(logger, level, ...) logger->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, level, __VA_ARGS__)

#if _DEBUG
	#define CORE_LOG_TRACE(...) LOG_WITH_DETAILS(VIEngine::Logger::GetCoreLogger(), spdlog::level::trace, __VA_ARGS__)
	#define CORE_LOG_DEBUG(...) LOG_WITH_DETAILS(VIEngine::Logger::GetCoreLogger(), spdlog::level::debug, __VA_ARGS__)
	#define CORE_LOG_INFO(...) LOG_WITH_DETAILS(VIEngine::Logger::GetCoreLogger(), spdlog::level::info, __VA_ARGS__)
	#define CORE_LOG_WARN(...) LOG_WITH_DETAILS(VIEngine::Logger::GetCoreLogger(), spdlog::level::warn, __VA_ARGS__)
	#define CORE_LOG_ERROR(...) LOG_WITH_DETAILS(VIEngine::Logger::GetCoreLogger(), spdlog::level::err, __VA_ARGS__)
	#define CORE_LOG_CRITICAL(...) LOG_WITH_DETAILS(VIEngine::Logger::GetCoreLogger(), spdlog::level::critical, __VA_ARGS__)

	#define LOG_TRACE(...) LOG_WITH_DETAILS(VIEngine::Logger::GetClientLogger(), spdlog::level::trace, __VA_ARGS__)
	#define LOG_DEBUG(...) LOG_WITH_DETAILS(VIEngine::Logger::GetClientLogger(), spdlog::level::debug, __VA_ARGS__)
	#define LOG_INFO(...) LOG_WITH_DETAILS(VIEngine::Logger::GetClientLogger(), spdlog::level::info, __VA_ARGS__)
	#define LOG_WARN(...) LOG_WITH_DETAILS(VIEngine::Logger::GetClientLogger(), spdlog::level::warn, __VA_ARGS__)
	#define LOG_ERROR(...) LOG_WITH_DETAILS(VIEngine::Logger::GetClientLogger(), spdlog::level::err, __VA_ARGS__)
	#define LOG_CRITICAL(...) LOG_WITH_DETAILS(VIEngine::Logger::GetClientLogger(), spdlog::level::critical, __VA_ARGS__)
#else
	#define CORE_LOG_TRACE(...)
	#define CORE_LOG_DEBUG(...)
	#define CORE_LOG_INFO(...)
	#define CORE_LOG_WARN(...)
	#define CORE_LOG_ERROR(...)
	#define CORE_LOG_CIRITICAL(...)

	#define LOG_TRACE(...)
	#define LOG_DEBUG(...)
	#define LOG_INFO(...)
	#define LOG_WARN(...)
	#define LOG_ERROR(...)
	#define LOG_CIRITICAL(...)
#endif