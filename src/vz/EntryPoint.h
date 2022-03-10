#pragma once
#include "Input.h"

#ifdef VZ_PLATFORM_WIN
int main()
{
	vz::Log::Init();

	VZ_CORE_INFO("Initialized");
	VZ_INFO("Initialized");
	auto app = vz::CreateApp();
	app->Start();

	delete app;
	return 0;
}
#endif