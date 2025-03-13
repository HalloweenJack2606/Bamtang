#pragma once

#include "Math/GLM/GLMDefinitions.h"
#include "HAL/PlatformDetection.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <queue>
#include <array>

#if PLATFORM_APPLE
    #include <stddef.h> //needed for size_t
#endif

// Unsigned Types
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef uint64 SIZE_T;

//Signed Types
typedef signed char int8;
typedef signed short int int16;
typedef signed int int32;
typedef signed long long int64;
typedef int64 SSIZE_T;

typedef std::string CString;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ASPECT_RATIO ((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)