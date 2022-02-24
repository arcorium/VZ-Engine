#include "vz/Vz.h"
#include "vz/event/MouseEvent.h"
#include "imgui.h"
#include "vz/layer/ImGuiLayer.h"


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
		//VZ_INFO("{} - Updated!", m_name);
	}
	void OnEvent(vz::Event& ev) override
	{
		vz::EventDispatcher ed{ ev };

		ed.Dispatch<vz::MouseButtonPressEvent>([this]<typename T>(T && args) { return OnMouseClick(std::forward<T>(args)); });
		ed.Dispatch<vz::KeyPressEvent>(VZ_BIND_EVENT_BOOL(OnKeyPressEvent));
	}

	bool OnMouseClick(vz::MouseButtonPressEvent& ev)
	{
		VZ_INFO("Mouse button pressed : {}", ev.ToString());

		return true;	// handled
	}

	bool OnKeyPressEvent(vz::KeyPressEvent& ev)
	{
		VZ_INFO("{} : {}", m_name, ev.GetKeyCode());
		return true;	// The event KeyPress will stop here
	}
};

class App : public vz::Application
{
public:
	App()
	{
		auto t = new LayerImpl;
		auto i = new vz::ImGuiLayer{m_window};
		PushLayer(t);
		PushOverlay(i);

	}
	~App() override
	{

	}

private:
};

APP(App)
