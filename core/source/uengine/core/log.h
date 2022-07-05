#pragma once

#include "export.h"

#include <spdlog/spdlog.h>

#include <memory>

namespace ue {
	class UE_API log {
	public:
		static std::shared_ptr<spdlog::logger>& get_core_logger() { return _core_logger; }
		static std::shared_ptr<spdlog::logger>& get_client_logger() { return _client_logger; }

		static void initialize();
	private:
		static std::shared_ptr<spdlog::logger> _core_logger;
		static std::shared_ptr<spdlog::logger> _client_logger;
	};
}

#define UE_CORE_TRACE(...)		::ue::log::get_core_logger()->trace(__VA_ARGS__)
#define UE_CORE_INFO(...)		::ue::log::get_core_logger()->info(__VA_ARGS__)
#define UE_CORE_DEBUG(...)		::ue::log::get_core_logger()->debug(__VA_ARGS__)
#define UE_CORE_WARNING(...)	::ue::log::get_core_logger()->warn(__VA_ARGS__)
#define UE_CORE_ERROR(...)		::ue::log::get_core_logger()->error(__VA_ARGS__)
#define UE_CORE_CRITICAL(...)	::ue::log::get_core_logger()->critical(__VA_ARGS__)

#define UE_TRACE(...)			::ue::log::get_client_logger()->trace(__VA_ARGS__)
#define UE_INFO(...)			::ue::log::get_client_logger()->info(__VA_ARGS__)
#define UE_DEBUG(...)			::ue::log::get_client_logger()->debug(__VA_ARGS__)
#define UE_WARNING(...)			::ue::log::get_client_logger()->warn(__VA_ARGS__)
#define UE_ERROR(...)			::ue::log::get_client_logger()->error(__VA_ARGS__)
#define UE_CRITICAL(...)		::ue::log::get_client_logger()->critical(__VA_ARGS__)