#include "vzpch.h"
#include "Application.h"
#include "imgui.h"
#include "Input.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Layer/ImGuiLayer.h"


namespace vz
{
	Application* Application::m_instance;


	Application::Application()
		: m_window(Window::Create()), m_imguiLayer(new ImGuiLayer{m_window})
	{
		m_instance = this;

		// Windows Settings
		VZ_ASSERT((m_window != nullptr), "Window is Null");
		m_running = true;
		PushOverlay(m_imguiLayer);

		// Bind using 'this' as parameter 1, because its needed to change method member into normal function
		// It wont needed to using bind if it using lambda expression
		/* m_window->SetEventCallback(std::bind(&OnEvent, this, std::placeholders::_1)); */
		// Better doing it on lambda (not normal lambda, but lambda for forwarding the bind function)
		m_window->SetEventCallback(VZ_BIND_EVENT_VOID(OnEvent));


		glCreateVertexArrays(1, &m_vao);
		//glBindVertexArray(m_vao);

		float vertices[] =
		{
			-0.8f, 0.8f, 0.0f,	// TL
			0.8f, 0.8f, 0.0f,	// TR
			0.8f, -0.8f, 0.0f,	// BR
			-0.8f, -0.8f, 0.0,	// BL
		};

		unsigned short indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		glCreateBuffers(1, &m_vbo);
		glNamedBufferData(m_vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glCreateBuffers(1, &m_ibo);
		glNamedBufferData(m_ibo, sizeof(indices), indices, GL_STATIC_DRAW);

		glEnableVertexArrayAttrib(m_vao, 0);
		glVertexArrayAttribBinding(m_vao, 0, 0);
		glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayVertexBuffer(m_vao, 0, m_vbo, 0, sizeof(float) * 3);
		glVertexArrayElementBuffer(m_vao, m_ibo);
	}

	Application::~Application()
	{
		VZ_DELETE(m_window);
	}

	void Application::Start()
	{

		while (m_running)
		{

			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_imguiLayer->Begin();

			glBindVertexArray(m_vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

			// Loop all layers
			for(auto& layer : m_layerManager)
			{
				// Update
				layer->OnUpdate();

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
