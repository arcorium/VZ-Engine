#include "vz/vz.h"
#include "vz/event/MouseEvent.h"
#include "imgui.h"
#include "vz/graphic/Renderer.h"

#include "vz/Camera.h"

namespace vz
{
	class Layer;
	class Time;
}

inline static float position = 0.0f;
inline static float rotate = 0.0f;


class LayerImpl : public vz::Layer
{
public:
	LayerImpl()
	: vz::Layer("Implementation"), m_shader(std::make_shared<vz::Shader>("basic")), m_camera(-2.0f, 2.0f, -2.0f, 2.0f)
	{

		float vertices[] =
		{
			-0.8f, 0.8f, 0.0f,	// TL
			0.8f, 0.8f, 0.0f,	// TR
			0.8f, -0.8f, 0.0f,	// BR
			-0.8f, -0.8f, 0.0,	// BL
		};

		unsigned int indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		m_vertexArray = vz::IVertexArray::CreateShared();

		std::shared_ptr<vz::IVertexBuffer> m_vbo = vz::IVertexBuffer::CreateShared(sizeof(vertices), vertices);
		std::shared_ptr<vz::IIndexBuffer> m_ibo =  vz::IIndexBuffer::CreateShared(sizeof(indices), indices);

		vz::BufferLayout layout{ {vz::ShaderType::Vec3F} };

		m_vbo->SetLayout(layout);

		m_vertexArray->AddVertexBuffer(m_vbo);
		m_vertexArray->SetIndexBuffer(m_ibo);

		m_shader->Load({ .Vertex = "assets/basic.vs", .Fragment = "assets/basic.fs" });
	}

	~LayerImpl() override {}

	void OnAttach() override
	{
		VZ_INFO("Attached");
	}

	void OnDetach() override
	{
		VZ_INFO("Detached");
	}

	void OnUpdate(vz::Time& time) override
	{
		if (vz::Input::IsKeyPressed(vz::Key::W))
		{
			const glm::vec3& currentPos = m_camera.GetPosition();
			m_position.y += time(m_cameraSpeed);
		}

		if (vz::Input::IsKeyPressed(vz::Key::S))
		{
			const glm::vec3& currentPos = m_camera.GetPosition();
			m_position.y -= time(m_cameraSpeed);
		}

		if (vz::Input::IsKeyPressed(vz::Key::A))
		{
			const glm::vec3& currentPos = m_camera.GetPosition();
			m_position.x -= time(m_cameraSpeed);
		}

		if (vz::Input::IsKeyPressed(vz::Key::D))
		{
			const glm::vec3& currentPos = m_camera.GetPosition();
			m_position.x += time(m_cameraSpeed);
		}

		m_camera.SetPosition(m_position);

	}

	void OnDraw() override
	{
		vz::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		vz::RenderCommand::Clear(vz::ClearFlag::COLOR | vz::ClearFlag::DEPTH);

		vz::Renderer::BeginScene(m_camera);
		{
			m_shader->Bind();
			vz::Renderer::Submit(m_shader, m_vertexArray);
		}
		vz::Renderer::EndScene();
	}

	void ImGuiDraw() override
	{

	}

	void OnEvent(vz::Event& ev) override
	{
		vz::EventDispatcher ed{ ev };

		ed.Dispatch<vz::MouseButtonPressEvent>([this]<typename T>(T && args) { return OnMouseClick(std::forward<T>(args)); });
		ed.Dispatch<vz::KeyPressEvent>(VZ_BIND_EVENT_BOOL(OnKeyPress));
	}

	bool OnMouseClick(vz::MouseButtonPressEvent& ev)
	{
		//VZ_INFO("Mouse button pressed : {}", ev.ToString());

		return true;	// handled
	}

	bool OnKeyPress(vz::KeyPressEvent& ev)
	{


		return false;	// Forward into keypress event on next layer
	}

private:
	std::shared_ptr<vz::IVertexArray> m_vertexArray;
	std::shared_ptr<vz::Shader> m_shader;
	vz::OrthographicCamera m_camera;

	glm::vec3 m_position{0.0f};
	float m_cameraSpeed = 3.0f;
};

class App : public vz::Application
{
public:
	App()
	{
		auto t = new LayerImpl;
		PushLayer(t);
		//PushOverlay(m_imguiLayer);	// By the application
	}
	~App() override
	{

	}


private:
};

APP(App)
