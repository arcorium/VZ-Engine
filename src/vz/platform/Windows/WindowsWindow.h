#pragma once
#include "vz/Window.h"
#include "vz/Core.h"

#include <GLFW/glfw3.h>

namespace vz
{
	class VZ_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProp& prop);

		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned GetWidth() const override { return m_data.Width; }
		unsigned GetHeight() const override { return m_data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_data.Callback = callback; }
		bool SetVSync(bool val) override;
		bool IsVSync() const override;

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