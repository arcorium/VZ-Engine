#pragma once
#include "event/Event.h"
#include "Core.h"

// Cross Platform handled by GLFW
#ifdef VZ_PLATFORM_WIN
	#define _GLFW_WIN32
#elif defined VZ_PLATFORM_UNIX
	#define _GLFW_X11
#endif

#include <GLFW/glfw3.h>

namespace vz
{
	// Window Property
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

	// Window Interface for desktop environment
	class VZ_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;

		virtual unsigned int GetHeight() const = 0;

		// Window Attribute
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool val) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProp& props = WindowProp());
	};

	// Implement of window, because the platform "native" specific windows is not built yet
	class VZ_API WindowImpl : public Window
	{
	public:
		WindowImpl(const WindowProp& prop);

		virtual ~WindowImpl();

		void OnUpdate() override;

		unsigned GetWidth() const override { return m_data.Width; }
		unsigned GetHeight() const override { return m_data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_data.Callback = callback; }
		void SetVSync(bool val) override;
		bool IsVSync() const override;

		static Window* Create(const WindowProp& props = WindowProp());

	private:
		virtual void Init(const WindowProp& prop);
		virtual void Quit();

	private:
		GLFWwindow* m_window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn Callback;
		} m_data;
	};
}