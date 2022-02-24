#pragma once

#ifdef VZ_BUILD
	#include "Define.h"
	#include "Application.h"
	#include "Log.h"
#include "vz/Layer.h"

	/// ENTRY POINT
	#include "EntryPoint.h"
	///	ENTRY POINT

#else
	#include "vz/Core.h"
#include "vz/Application.h"
	#include "vz/Log.h"
#include "vz/Layer.h"

	/// ENTRY POINT
	#include "vz/EntryPoint.h"
	///	ENTRY POINT
#endif