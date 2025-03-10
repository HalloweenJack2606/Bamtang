#pragma once

#ifdef _WIN32
#ifdef _WIN64
		#define PLATFORM_WINDOWS 1
	#else
		#error "x86 is not supported"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define PLATFORM_APPLE 1
#elif defined(__linux__)
    #define PLATFORM_LINUX 1
	#error "Linux is not supported"
#else
	#error "Unknown platform"
#endif
