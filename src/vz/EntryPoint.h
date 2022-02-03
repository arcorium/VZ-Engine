#pragma once

extern vz::Application* vz::CreateApp();	// The declaration is somewhere (client) not here (server)

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
