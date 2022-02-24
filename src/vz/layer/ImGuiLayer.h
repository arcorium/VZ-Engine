#pragma once
#include "vz/Core.h"
#include "vz/Layer.h"
#include "vz/Window.h"
#include "vz/event/MouseEvent.h"
#include "vz/event/KeyEvent.h"
#include "vz/event/ApplicationEvent.h"

namespace vz
{
	class VZ_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(Window*& window);
		~ImGuiLayer() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		/**
		 * \brief Will be called every frame when it is on LayerManager instance
		 * \param ev event
		 */
		void OnEvent(Event& ev) override;

	private:
		void Clean();
		void Init();

		bool OnMouseMove(MouseMoveEvent& ev);
		bool OnMouseScroll(MouseScrollEvent& ev);
		bool OnMouseButtonPress(MouseButtonPressEvent& ev);
		bool OnMouseButtonRelease(MouseButtonReleaseEvent& ev);
		bool OnKeyPress(KeyPressEvent& ev);
		bool OnKeyRelease(KeyReleaseEvent& ev);
		bool OnKeyType(KeyTypeEvent& ev);
		bool OnWindowResize(WindowResizeEvent& ev);
		bool OnWindowClose(WindowCloseEvent& ev);


	private:
		Window*& m_window;
		float m_time;
	};
}
