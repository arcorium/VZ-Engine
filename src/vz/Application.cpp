#include "Application.h"

#include "imgui.h"
#include "Input.h"
#include "vzpch.h"
#include "GLFW/glfw3.h"
#include "graphic/Renderer.h"
#include "Layer/ImGuiLayer.h"


namespace vz
{
	Application* Application::s_instance;


	Application::Application()
		: m_window(Window::Create()), m_imguiLayer(new ImGuiLayer{m_window}), m_shader("basic")
	{
		s_instance = this;

		// Windows Settings
		VZ_ASSERT((m_window != nullptr), "Window is Null");
		m_running = true;
		PushOverlay(m_imguiLayer);

		// Bind using 'this' as parameter 1, because its needed to change method member into normal function
		// It wont needed to using bind if it using lambda expression
		/* m_window->SetEventCallback(std::bind(&OnEvent, this, std::placeholders::_1)); */
		// Better doing it on lambda (not normal lambda, but lambda for forwarding the bind function)
		m_window->SetEventCallback(VZ_BIND_EVENT_VOID(OnEvent));
		m_window->SetVSync(true);

		// Set shader path
		Shader::SetPath("../../../../", true);
	}

	Application::~Application()
	{
		VZ_DELETE(m_window);

		if (Input::Get())
			delete Input::Get();
	}

	void Application::Start()
	{
		Time time;
		while (m_running)
		{

			// Calculating delta time
			time.CalculateDelta();

			m_imguiLayer->Begin();

			// Loop all layers

			for (auto& layer : m_layerManager)
			{
				// Update
				layer->OnUpdate(time);
			}

			for(auto& layer : m_layerManager)
			{
				// Draw
				layer->OnDraw();

				// Render ImGui things
				layer->ImGuiDraw();
			}

			m_imguiLayer->End();

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

		// Dispatch event from back layer (overlay layer will got hit first)
		for(auto it = m_layerManager.end(); it != m_layerManager.begin();)
		{
			(*--it)->OnEvent(e);

			// Prevent same event will be handled twice or more
			if (e.IsHandled())
				break;
		}

		ed.Dispatch<WindowCloseEvent>(VZ_BIND_EVENT_BOOL(OnWindowClose));
		ed.Dispatch<KeyPressEvent>(VZ_BIND_EVENT_BOOL(OnKeyPress));

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		VZ_CORE_INFO("Window Closed");
		m_running = false;	// Terminate application
		return true;
	}

	bool Application::OnKeyPress(KeyPressEvent& e)
	{
		VZ_INFO("Its on {}", __FILE__);
		return true;
	}
}
