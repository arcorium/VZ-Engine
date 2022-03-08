#include "WindowsWindow.h"
#include "vz/Log.h"

#include "vz/event/ApplicationEvent.h"
#include "vz/event/KeyEvent.h"
#include "vz/event/MouseEvent.h"

#include "GLFW/glfw3.h"

namespace vz
{
	namespace
	{
		bool m_isGLFWInitialized = false;
	}

	WindowsWindow::WindowsWindow(const WindowProp& prop)
		: m_window(nullptr)
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
		//glfwSwapBuffers(m_window);
		m_context->SwapBuffers();
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

	void WindowsWindow::Show() const
	{
		glfwShowWindow(m_window);
	}

	void WindowsWindow::Init(const WindowProp& prop)
	{
		// Window data
		m_data.Width = prop.Width;
		m_data.Height = prop.Height;
		m_data.Title = prop.Title;

		// GLFW
		VZ_CORE_INFO("Creating window {} ({}, {})", m_data.Title, m_data.Width, m_data.Height);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_VISIBLE, 0);
		if (!m_isGLFWInitialized)
		{
			VZ_ASSERT(glfwInit(), "Failed to instantiate GLFW");

			m_isGLFWInitialized = true;
		}

		m_window = glfwCreateWindow(INT(m_data.Width), INT(m_data.Height), m_data.Title.c_str(), nullptr, nullptr);

		SetVSync(true);

		// Create and init context
		m_context = new ctx::OpenGL{ m_window };

		m_context->Init();

		glfwSetWindowUserPointer(m_window, &m_data);

		// GLFW Callback
		InitCallback();
	}

	void WindowsWindow::InitCallback()
	{
		// GLFW Callbacks
		// Window
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* win, int width, int height)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(win));

				data.Width = width;
				data.Height = height;

				WindowResizeEvent e{ (data.Width), (data.Height) };
				data.Callback(e);

			});

		// Keyboard
		glfwSetKeyCallback(m_window, [](GLFWwindow* win, int key, int scancode, int action, int mods)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(win));


				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressEvent events{ key, mods, 0 };
					data.Callback(events);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent events{ key };
					data.Callback(events);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent events{ key, mods, 1 };
					data.Callback(events);
					break;
				}
				}
			});

		glfwSetCharCallback(m_window, [](GLFWwindow* win, unsigned int keycode)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(win));

				KeyTypeEvent ev{ static_cast<int>(keycode) };
				data.Callback(ev);

			});

		// Mouse
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* win, double x, double y)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(win));

				MouseMoveEvent events{ static_cast<float>(x), static_cast<float>(y) };
				data.Callback(events);

			});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* win, int button, int action, int mods)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(win));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent events{ button, mods };
					data.Callback(events);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent events{ button };
					data.Callback(events);
					break;
				}
				}

			});

		glfwSetScrollCallback(m_window, [](GLFWwindow* win, double xOffset, double yOffset)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(win));

				MouseScrollEvent events{ static_cast<float>(xOffset), static_cast<float>(yOffset) };
				data.Callback(events);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* win)
			{
				auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(win));

				WindowCloseEvent events;
				data.Callback(events);
			});
	}

	void WindowsWindow::Quit()
	{

		glfwDestroyWindow(m_window);
		glfwTerminate();

		delete m_context;
	}

}
