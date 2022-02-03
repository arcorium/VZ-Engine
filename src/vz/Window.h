#pragma once
#include "event/Event.h"
#include "Core.h"

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
		virtual bool SetVSync(bool val) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProp& props = WindowProp());
	};
}