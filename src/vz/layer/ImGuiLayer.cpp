#include "vzpch.h"
#include "ImGuiLayer.h"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "GLFW/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"
#include "vz/Application.h"

namespace vz
{
	ImGuiLayer::ImGuiLayer(Window*& window)
		: Layer("ImGuiLayer"), m_window(window), m_time(0)
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		Clean();
	}

	void ImGuiLayer::OnAttach()
	{
		Init();
	}

	void ImGuiLayer::OnDetach()
	{
		Clean();
	}

	void ImGuiLayer::OnUpdate()
	{
		Application& app = Application::Get();
		ImGuiIO& io = ImGui::GetIO();

		// Set time
		float currentTime = FLOAT(glfwGetTime());
		m_time = (m_time > 0.0f) ? (currentTime - m_time) : (1.0f / 60.0f);

		io.DeltaTime = m_time;
		//io.DisplaySize = ImVec2(FLOAT(app.GetWindow().GetWidth()), FLOAT(app.GetWindow().GetHeight()));

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;

		if (show)
		{
			ImGui::ShowDemoWindow(&show);
		}

		m_time = currentTime;

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& ev)
	{
		EventDispatcher ed{ev};

		ed.Dispatch<KeyPressEvent>(VZ_BIND_EVENT_BOOL(OnKeyPress));
		ed.Dispatch<KeyReleaseEvent>(VZ_BIND_EVENT_BOOL(OnKeyRelease));
		ed.Dispatch<KeyTypeEvent>(VZ_BIND_EVENT_BOOL(OnKeyType));
		ed.Dispatch<MouseMoveEvent>(VZ_BIND_EVENT_BOOL(OnMouseMove));
		ed.Dispatch<MouseButtonPressEvent>(VZ_BIND_EVENT_BOOL(OnMouseButtonPress));
		ed.Dispatch<MouseButtonReleaseEvent>(VZ_BIND_EVENT_BOOL(OnMouseButtonRelease));
		ed.Dispatch<MouseScrollEvent>(VZ_BIND_EVENT_BOOL(OnMouseScroll));
		ed.Dispatch<WindowResizeEvent>(VZ_BIND_EVENT_BOOL(OnWindowResize));
		ed.Dispatch<WindowCloseEvent>(VZ_BIND_EVENT_BOOL(OnWindowClose));
	}

	void ImGuiLayer::Init()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ClipboardUserData = m_window->Get();
		io.ImeWindowHandle = static_cast<void*>(glfwGetWin32Window(m_window->Get()));

		// Temporary
		// TODO: Use VZ-Engine keycode
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		vz::Application& app = vz::Application::Get();
		io.DisplaySize = ImVec2(FLOAT(app.GetWindow().GetWidth()), FLOAT(app.GetWindow().GetHeight()));

		ImGui_ImplOpenGL3_Init("#version 460 core");
	}

	bool ImGuiLayer::OnMouseMove(MouseMoveEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2{ ev.GetX(), ev.GetY() };

		return false;
	}

	bool ImGuiLayer::OnMouseScroll(MouseScrollEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += ev.GetY();
		io.MouseWheelH += ev.GetX();
		return false;
	}

	bool ImGuiLayer::OnMouseButtonPress(MouseButtonPressEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev.GetButton()] = true;

		io.KeyAlt = ev.GetModifier() == GLFW_KEY_LEFT_ALT || ev.GetModifier() == GLFW_KEY_RIGHT_ALT;
		io.KeyCtrl = ev.GetModifier() == GLFW_KEY_LEFT_CONTROL || ev.GetModifier() == GLFW_KEY_RIGHT_CONTROL;
		io.KeyShift = ev.GetModifier() == GLFW_KEY_LEFT_SHIFT || ev.GetModifier() == GLFW_KEY_RIGHT_SHIFT;
		io.KeySuper = ev.GetModifier() == GLFW_KEY_LEFT_SUPER || ev.GetModifier() == GLFW_KEY_RIGHT_SUPER;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonRelease(MouseButtonReleaseEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ev.GetButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyPress(KeyPressEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ev.GetKeyCode()] = true;

		io.KeyAlt = ev.GetModifier() == GLFW_KEY_LEFT_ALT || ev.GetModifier() == GLFW_KEY_RIGHT_ALT;
		io.KeyCtrl = ev.GetModifier() == GLFW_KEY_LEFT_CONTROL || ev.GetModifier() == GLFW_KEY_RIGHT_CONTROL;
		io.KeyShift = ev.GetModifier() == GLFW_KEY_LEFT_SHIFT || ev.GetModifier() == GLFW_KEY_RIGHT_SHIFT;
		io.KeySuper = ev.GetModifier() == GLFW_KEY_LEFT_SUPER || ev.GetModifier() == GLFW_KEY_RIGHT_SUPER;

		return false;	// IF true: It will stop here (not executing event on layer after)
	}

	bool ImGuiLayer::OnKeyType(KeyTypeEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();

		// Set Character
		if (ev.GetKeyCode() > 0 && ev.GetKeyCode() < 0x100000)
			io.AddInputCharacter(ev.GetKeyCode());

		return false;
	}


	bool ImGuiLayer::OnKeyRelease(KeyReleaseEvent& ev)
	{

		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[ev.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& ev)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2{ FLOAT(ev.GetWidth()), FLOAT(ev.GetHeight()) };
		
		return false;
	}

	bool ImGuiLayer::OnWindowClose(WindowCloseEvent& ev)
	{
		return false;
	}

	void ImGuiLayer::Clean()
	{
		ImGui_ImplOpenGL3_Shutdown();
		//ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}


}
