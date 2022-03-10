#pragma once
#include "vz/Core.h"
#include "vz/Window.h"
#include "vz/graphic/OpenGL/OpenGLContext.h"

struct GLFWwindow;

namespace vz
{
	class VZ_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProp& prop);

		~WindowsWindow() override;

		void OnUpdate() override;

		int GetWidth() const override { return m_data.Width; }
		int GetHeight() const override { return m_data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_data.Callback = callback; }
		void SetVSync(bool val) override;
		bool IsVSync() const override;

		static Window* Create(const WindowProp& props = WindowProp());

		void* Get() const override { return m_window; }

		/**
		 * \brief Show the window
		 */
		void Show() const;

	private:
		void Init(const WindowProp& prop);
		void InitCallback();
		void Quit();

	private:
		GLFWwindow* m_window;
		ctx::Context* m_context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn Callback;
		} m_data;
	};
}
