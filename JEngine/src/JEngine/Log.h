#pragma once
#pragma warning (disable:4251)
#include <JEpch.h>

#include "core.h"

#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h" 

namespace JEngine {

	class JE_API Log
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

#define JE_CORE_ERROR(...)    ::JEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define JE_CORE_WARN(...)     ::JEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define JE_CORE_INFO(...)     ::JEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define JE_CORE_TRACE(...)    ::JEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define JE_CORE_FATAL(...)    ::JEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define JE_CLIENT_ERROR(...)    ::JEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define JE_CLIENT_WARN(...)     ::JEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define JE_CLIENT_INFO(...)     ::JEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define JE_CLIENT_TRACE(...)    ::JEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define JE_CLIENT_FATAL(...)    ::JEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

