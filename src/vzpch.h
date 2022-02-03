#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// Platform specific

#if defined VZ_PLATFORM_WIN
#include <Windows.h>
#elif defined VZ_PLATFORM_UNIX
#include <unistd.h>
#endif