#pragma once
#include "Core.h"
#include "Layer.h"
#include "LayerManager.h"
#include "Window.h"
#include "event/ApplicationEvent.h"
#include "event/KeyEvent.h"


namespace vz
{
	class ImGuiLayer;

	class VZ_API Application
	{
		friend Application* CreateApp();

	protected:
		// Only allowing friend function and derived class to construct
		Application();

	public:
		/**
		 * \brief Callback passed into window to handle event that occur
		 * \param e event 
		 */
		void OnEvent(Event& e);
		
		virtual ~Application();

		/**
		 * \brief Starting the game
		 */
		void Start();

		/**
		 * \brief Pushing layer into layer manager
		 * \param layer layer child(heap allocated)
		 */
		void PushLayer(Layer* layer);

		/**
		 * \brief Pushing overlay layer into manager in last position
		 * \param layer layer child(heap allocated)
		 */
		void PushOverlay(Layer* layer);

		/**
		 * \brief Get last application created
		 * \return application instance address
		 */
		static Application& Get() {	return *m_instance;	}

		/**
		 * \brief Get window bound to the application
		 * \return window in application
		 */
		Window* GetWindow() const { return m_window; }

	private:
		/**
		 * \brief Handle when the window is closed
		 * \param e WindowCloseEvent
		 * \return handled or not
		 */
		bool OnWindowClose(WindowCloseEvent& e);

		/**
		 * \brief Handle key press event
		 * \param e KeyPressEvent
		 * \return handled or not
		 */
		bool OnKeyPress(KeyPressEvent& e);

	protected:
		Window* m_window;
		bool	m_running;

		LayerManager m_layerManager;

	private:
		// Application layer
		ImGuiLayer* m_imguiLayer;
		// Singleton application
		static Application* m_instance;

		// Graphics stuffs
		unsigned m_vao, m_vbo, m_ibo;
	};

	extern Application* CreateApp(); // The declaration is somewhere (client) not here (server)
}
