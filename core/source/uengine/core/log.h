#pragma once

#include "memory.h"

#include <spdlog/spdlog.h>

namespace ue {
	class log {
	public:
		static const reference<spdlog::logger>& get_core_logger() { return _core_logger; }
		static const reference<spdlog::logger>& get_client_logger() { return _client_logger; }

		static void initialize();
	private:
		static reference<spdlog::logger> _core_logger;
		static reference<spdlog::logger> _client_logger;
	};
}

#define UE_CORE_LOG_TRACE(...)		::ue::log::get_core_logger()->trace(__VA_ARGS__)
#define UE_CORE_LOG_INFO(...)		::ue::log::get_core_logger()->info(__VA_ARGS__)
#define UE_CORE_LOG_DEBUG(...)		::ue::log::get_core_logger()->debug(__VA_ARGS__)
#define UE_CORE_LOG_WARNING(...)	::ue::log::get_core_logger()->warn(__VA_ARGS__)
#define UE_CORE_LOG_ERROR(...)		::ue::log::get_core_logger()->error(__VA_ARGS__)
#define UE_CORE_LOG_CRITICAL(...)	::ue::log::get_core_logger()->critical(__VA_ARGS__)

#define UE_LOG_TRACE(...)			::ue::log::get_client_logger()->trace(__VA_ARGS__)
#define UE_LOG_INFO(...)			::ue::log::get_client_logger()->info(__VA_ARGS__)
#define UE_LOG_DEBUG(...)			::ue::log::get_client_logger()->debug(__VA_ARGS__)
#define UE_LOG_WARNING(...)			::ue::log::get_client_logger()->warn(__VA_ARGS__)
#define UE_LOG_ERROR(...)			::ue::log::get_client_logger()->error(__VA_ARGS__)
#define UE_LOG_CRITICAL(...)		::ue::log::get_client_logger()->critical(__VA_ARGS__)