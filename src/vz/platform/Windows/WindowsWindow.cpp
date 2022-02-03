#include "WindowsWindow.h"

namespace vz
{
	static bool isGLFWInitialized = false;

	WindowsWindow::WindowsWindow(const WindowProp& prop)
	{
		Init(prop);
	}

	WindowsWindow::~WindowsWindow()
	{

	}

	void WindowsWindow::OnUpdate()
	{
	}

	bool WindowsWindow::SetVSync(bool val)
	{
		m_data.VSync = val;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_data.VSync;
	}

	void WindowsWindow::Init(const WindowProp& prop)
	{
	}

	void WindowsWindow::Quit()
	{
	}

	Window* Create(const WindowProp& props = WindowProp())
	{
		return new WindowsWindow(props);
	}
}
