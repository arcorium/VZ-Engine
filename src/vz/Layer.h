#pragma once

#include "Core.h"
#include "util/Timestamp.h"
#include <string>
#include "event/Event.h"

namespace vz
{
	class VZ_API Layer
	{

	public:
		/**
		 * \brief Constructor
		 * \param name name of layer instance
		 */
		Layer(const std::string& name = "Layer");

		/**
		 * \brief virtual destructor
		 */
		virtual ~Layer();

		/**
		 * \brief Called when the layer is attached or pushed into manager
		 */
		virtual void OnAttach();

		/**
		 * \brief Called when the layer is detached or pop from manager
		 */
		virtual void OnDetach();

		/**
		 * \brief Called every frame for updating when the layer is already attached or pushed into manager
		 */
		virtual void OnUpdate(Time& time);

		/**
		 * \brief Called every frame for drawing when the layer is already attached or pushed into manager
		 */
		virtual void OnDraw();

		/**
		 * \brief Called every frame and in the last section (so the gui will drawn in top most)
		 */
		virtual void ImGuiDraw();

		/**
		 * \brief Called when event is occur (Child class should dispatch event to make it work for every event)
		 * \param ev event occurred
		 */
		virtual void OnEvent(Event& ev);

		/**
		 * \brief Get layer's name
		 * \return name of the layer
		 */
		[[nodiscard]] const std::string& GetName() const;

		/**
		 * \brief Get layer's unique id
		 * \return Layer id
		 */
		[[nodiscard]] unsigned GetId() const;

	protected:
		std::string m_name;		// layer class name
		unsigned m_id;			// layer unique id

		inline static unsigned m_totalLayer = 0;
	};
}