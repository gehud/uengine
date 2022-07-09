#pragma once

#include "log.h"

#ifdef UE_DEBUG
	#define UE_CORE_ASSERT(condition, ...) if (!(condition)) { UE_CORE_LOG_ERROR(__VA_ARGS__); __debugbreak(); }
	#define UE_ASSERT(condition, ...) if (!(condition)) { UE_LOG_ERROR(__VA_ARGS__); __debugbreak(); }
#else
	#define UE_CORE_ASSERT(condition, ...)
	#define UE_ASSERT(condition, ...)
#endif