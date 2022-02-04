#include "vzpch.h"
#include "Window.h"

#ifdef VZ_PLATFORM_WIN
	#include "platform/Windows/WindowsWindow.h"
	typedef vz::WindowsWindow PlatformWindow;
#elif defined VZ_PLATFORM_UNIX
	//#error "Currently not supporting yet"
	#include "platform/Windows/WindowsWindow.h"
	typedef vz::WindowsWindow PlatformWindow;
#endif


namespace vz
{
	Window* Window::Create(const WindowProp& props)
	{
//#ifdef VZ_PLATFORM_WIN
		return WindowImpl::Create(props);
//#endif
	}

	static bool m_isGLFWInitialized = false;

	WindowImpl::WindowImpl(const WindowProp& prop)
	{
		Init(prop);
	}

	WindowImpl::~WindowImpl()
	{
		Quit();
	}

	void WindowImpl::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowImpl::SetVSync(bool val)
	{
		if (val)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = val;
	}

	bool WindowImpl::IsVSync() const
	{
		return m_data.VSync;
	}

	Window* WindowImpl::Create(const WindowProp& props)
	{
		return new WindowsWindow{ props };
	}

	void WindowImpl::Init(const WindowProp& prop)
	{
		m_data.Width = prop.Width;
		m_data.Height = prop.Height;
		m_data.Title = prop.Title;
		m_data.VSync = true;


		VZ_CORE_INFO("Creating window {} ({}, {})", m_data.Title, m_data.Width, m_data.Height);

		if (!m_isGLFWInitialized)
		{
			VZ_ASSERT(glfwInit(), "Failed to instantiate GLFW");

			m_isGLFWInitialized = true;
		}

		m_window = glfwCreateWindow(INT(m_data.Width), INT(m_data.Height), m_data.Title.c_str(), nullptr, nullptr);

		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
	}

	void WindowImpl::Quit()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

}