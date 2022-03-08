#include "vz/Vz.h"
#include "vz/event/MouseEvent.h"
#include "imgui.h"
#include "vz/layer/ImGuiLayer.h"
#include "vz/renderer/Context.h"
#include "vz/renderer/OpenGLContext.h"


class LayerImpl : public vz::Layer
{
public:
	LayerImpl() : vz::Layer("Implementation") {}
	~LayerImpl() override {}
	void OnAttach() override
	{
		VZ_INFO("Attached");
	}

	void OnDetach() override
	{
		VZ_INFO("Detached");
	}

	void OnUpdate() override
	{

	}

	void OnDraw() override
	{

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
		if (vz::Input::IsKeyPressed(vz::Key::A))
		{
			VZ_INFO("A is Pressed");
			return true;	// Handled
		}
		return false;	// The event KeyPress will stop here
	}
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
