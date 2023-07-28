#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hana
{
	class HANA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define HN_CORE_TRACE(...)    ::Hana::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HN_CORE_INFO(...)     ::Hana::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HN_CORE_WARN(...)     ::Hana::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HN_CORE_ERROR(...)    ::Hana::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HN_CORE_CRITICAL(...) ::Hana::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HN_TRACE(...)         ::Hana::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HN_INFO(...)          ::Hana::Log::GetClientLogger()->info(__VA_ARGS__)
#define HN_WARN(...)          ::Hana::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HN_ERROR(...)         ::Hana::Log::GetClientLogger()->error(__VA_ARGS__)
#define HN_CRITICAL(...)      ::Hana::Log::GetClientLogger()->critical(__VA_ARGS__)
