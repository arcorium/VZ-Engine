#pragma once

#include "Event.h"

namespace vz
{
	// Window
	/**
	 * \brief Window resize handle
	 */
	class VZ_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned x, unsigned y)
			: Event(), m_x(x), m_y(y) {}

		/**
		 * \brief Get window width after resized
		 * \return width window
		 */
		int GetWidth() { return m_x; }

		/**
		 * \brief Get window height after resized
		 * \return height window
		 */
		int GetHeight() { return m_y; }

#ifdef VZ_DEBUG
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent : " << m_x << ", " << m_y;
			return ss.str();
		}
#endif

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		// Width and Height
		int m_x, m_y;
	};

	/**
	 * \brief Window close handle
	 */
	class VZ_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	};

	/**
	 * \brief Superclass of application event
	 */
	class VZ_API ApplicationEvent : public Event
	{
	public:
		ApplicationEvent() {}
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	/**
	 * \brief Application tick handle
	 */
	class VZ_API ApplicationTickEvent : public ApplicationEvent
	{
	public:
		ApplicationTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
	};

	/**
	 * \brief Application update handle
	 */
	class VZ_API ApplicationUpdateEvent : public ApplicationEvent
	{
	public:
		ApplicationUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
	};

	/**
	 * \brief Application render handle
	 */
	class VZ_API ApplicationRenderEvent : public ApplicationEvent
	{
		ApplicationRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
	};


}
