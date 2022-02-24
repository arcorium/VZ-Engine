#pragma once

#include "Core.h"
#include <string>
#include "event/Event.h"

namespace vz
{
	class VZ_API Layer
	{

	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();
		virtual void OnEvent(Event& ev);

		const std::string& GetName() const;
		unsigned GetId() const;

	protected:
		// String and name is the id of the layer, but the id is unique 
		std::string m_name;
		unsigned m_id;

		inline static unsigned m_totalLayer = 0;
	};
}