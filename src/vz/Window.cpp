#include "vzpch.h"
#include "Window.h"
#include "Log.h"
#include <GLFW/glfw3.h>

namespace vz
{
	void Window::Init()
	{
		if (!glfwInit())
		{
			VZ_CORE_CRITICAL("GLFW failed to init");
		}

		VZ_CORE_INFO("GLFW Init");
	}
}

