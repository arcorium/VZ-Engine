#pragma once
#include "Core.h"
#include "Layer.h"
#include "LayerManager.h"
#include "Window.h"
#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"

namespace vz
{
	class VZ_API Application
	{
		friend Application* CreateApp();

	protected:
		// Only allowing friend function and derived class to construct
		Application();

	public:

		void OnEvent(Event& e);
		
		virtual ~Application();

		void Start();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static Application& Get() {	return *m_instance;	}
		Window& GetWindow() const { return *m_window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPress(KeyPressEvent& e);

	protected:
		Window* m_window;
		bool	m_running;

		LayerManager m_layerManager;

	private:
		static Application* m_instance;
	};

	extern Application* CreateApp(); // The declaration is somewhere (client) not here (server)
}
