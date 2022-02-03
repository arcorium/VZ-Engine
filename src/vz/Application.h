#pragma once
#include "Core.h"

namespace vz
{
	class VZ_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Start();
	};

	Application* CreateApp();
}