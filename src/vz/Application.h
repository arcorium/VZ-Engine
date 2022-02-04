#pragma once
#include "Core.h"
#include "Window.h"

namespace vz
{
	class VZ_API Application
	{

	public:
		Application();
		virtual ~Application();

		void Start();

	private:
		Window* m_window;
	};

	Application* CreateApp();
}