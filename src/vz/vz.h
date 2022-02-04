#pragma once

#ifdef VZ_BUILD
				#include "Application.h"
				#include "Log.h"

				/// ENTRY POINT
				#include "EntryPoint.h"
				///	ENTRY POINT

#else
				#include "vz/Application.h"
				#include "vz/Log.h"

				/// ENTRY POINT
				#include "vz/EntryPoint.h"
				///	ENTRY POINT
#endif