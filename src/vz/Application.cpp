#include "vzpch.h"
#include "Application.h"
#include "imgui.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace vz
{
	Application* Application::m_instance;


	Application::Application()
	{
		m_window = Window::Create();
		m_instance = this;

		// Windows Settings
		VZ_ASSERT((m_window != nullptr), "Window is Null");
		m_running = true;

		// Bind using 'this' as parameter 1, because its needed to change method member into normal function
		// It wont needed to using bind if it using lambda expression
		/* m_window->SetEventCallback(std::bind(&OnEvent, this, std::placeholders::_1)); */
		// Better doing it on lambda (not normal lambda, but lambda for forwarding the bind function)
		m_window->SetEventCallback(VZ_BIND_EVENT_VOID(OnEvent));
	}

	Application::~Application()
	{
		VZ_SAFE_DELETE(m_window);
	}

	void Application::Start()
	{

		while (m_running)
		{

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Updating all layers
			for(auto& layer : m_layerManager)
			{
				layer->OnUpdate();
			}

			m_window->OnUpdate();	// Polling event and swap buffers
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerManager.Push(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_layerManager.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		//VZ_INFO("{}", e.ToString());

		EventDispatcher ed{ e };

		ed.Dispatch<WindowCloseEvent>(VZ_BIND_EVENT_BOOL(OnWindowClose));
		ed.Dispatch<KeyPressEvent>(VZ_BIND_EVENT_BOOL(OnKeyPress));

		// Dispatch event from back layer (overlay layer will got hit first)
		for(auto it = m_layerManager.end(); it != m_layerManager.begin();)
		{
			(*--it)->OnEvent(e);

			// Prevent same event will be handled twice or more
			if (e.IsHandled())
				break;
		}

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		VZ_CORE_INFO("Window Closed");
		m_running = false;	// Terminate application
		return true;
	}

	bool Application::OnKeyPress(KeyPressEvent& e)
	{
		return true;
	}
}
