#include "log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace ue {
	reference<spdlog::logger> log::_core_logger;
	reference<spdlog::logger> log::_client_logger;

	void log::initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		_core_logger = spdlog::stdout_color_mt("UEngine");
		_core_logger->set_level(spdlog::level::trace);
		_client_logger = spdlog::stdout_color_mt("Application");
		_client_logger->set_level(spdlog::level::trace);
	}
}