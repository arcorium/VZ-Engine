#pragma once
#include "vz/Core.h"
#include "vz/Layer.h"
#include "vz/Window.h"

/**
 * \brief Implementation of layer for ImGui
 */
namespace vz
{
	class VZ_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(Window*& window);
		~ImGuiLayer() override;
		void OnAttach() override;
		void OnDetach() override;
		void OnDraw() override;
		void ImGuiDraw() override;

		/**
		 * \brief Set new frame of ImGui layer
		 */
		void Begin();

		/**
		 * \brief Rendering the 'draw data'
		 */
		void End();

	private:
		void Clean();
		void Init();


	private:
		Window*& m_window;
		float m_time;
	};
}
