#pragma once

#ifdef UE_WINDOWS
	#ifdef UE_BUILD_SHARED
		#ifdef UE_DLL_EXPORTS
			#define UE_API __declspec(dllexport)
		#else
			#define UE_API __declspec(dllimport)
		#endif
	#else
		#define UE_API
	#endif
#else
	#define UE_API
#endif