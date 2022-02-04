#include "vzpch.h"
#include "Application.h"

namespace vz
{
	Application::Application()
	{
		m_window = Window::Create();
	}

	Application::~Application()
	{
		delete m_window;
	}

	void Application::Start()
	{
		while (true)
		{
			m_window->OnUpdate();
		}
	}
}
