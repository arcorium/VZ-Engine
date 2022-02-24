#include "WindowsWindow.h"
#include "vz/Log.h"

namespace vz
{
	static bool isGLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProp& prop)
	{
		Init(prop);
	}

	WindowsWindow::~WindowsWindow()
	{
		Quit();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVSync(bool val)
	{
		if (val)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = val;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_data.VSync;
	}

	Window* WindowsWindow::Create(const WindowProp& props)
	{
		return new WindowsWindow{ props };
	}

	void WindowsWindow::Init(const WindowProp& prop)
	{
		m_data.Width	= prop.Width;
		m_data.Height	= prop.Height;
		m_data.Title	= prop.Title;
		m_data.VSync	= true;


		VZ_CORE_INFO("Creating window {} ({}, {})", m_data.Title, m_data.Width, m_data.Height);

		if (!isGLFWInitialized)
		{
			VZ_ASSERT(glfwInit(), "Failed to instantiate GLFW");

			isGLFWInitialized = true;
		}

		m_window = glfwCreateWindow(INT(m_data.Width), INT(m_data.Height), m_data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
	}

	void WindowsWindow::Quit()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}
}
