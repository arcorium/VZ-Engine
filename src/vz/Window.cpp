#include "vzpch.h"
#include "Window.h"

#ifdef VZ_PLATFORM_WIN
	#include "platform/Windows/WindowsWindow.h"
	typedef vz::WindowsWindow PlatformWindow;
#elif defined VZ_PLATFORM_UNIX
	//#error "Currently not supporting yet"
	#include "platform/Windows/Window.h"
	typedef vz::WindowsWindow PlatformWindow;
#endif


namespace vz
{
	Window* Window::Create(const WindowProp& props)
	{
		return VZ_DO_PER_PLATFORM(PlatformWindow::Create, PlatformWindow::Create, props);
	}
	
}
