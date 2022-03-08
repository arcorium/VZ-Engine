#pragma once
#include "event/Event.h"
#include "Core.h"

// Cross Platform handled by GLFW
#ifdef VZ_PLATFORM_WIN
	#define _GLFW_WIN32
#elif defined VZ_PLATFORM_UNIX
	#define _GLFW_X11
#elif defined VZ_PLATFORM_UNIX_WAYLAND
#	define _GLFW_WAYLAND
#endif

namespace vz
{
	/**
	 * \brief Window properties
	 */
	struct WindowProp
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProp(const std::string& title = "VZ Engine",
		unsigned int width = 1280,
		unsigned int height = 720)
		: Title(title), Width(width), Height(height)
		{

		}

	};

	/**
	 * \brief Window interface for every desktop environment
	 */
	class VZ_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		/**
		 * \brief Default constructor
		 */
		Window() = default;

		/**
		 * \brief Virtual destructor
		 */
		virtual ~Window() {}

		/**
		 * \brief Called every last frames for update
		 */
		virtual void OnUpdate() = 0;

		/**
		 * \brief Get window width
		 * \return window width
		 */
		virtual int GetWidth() const = 0;

		/**
		 * \brief Get window height
		 * \return window height
		 */
		virtual int GetHeight() const = 0;

		// Window Attribute
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool val) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* Get() const = 0;

		static Window* Create(const WindowProp& props = WindowProp());
	};

	// Implement of window, because the platform "native" specific windows is not built yet
}