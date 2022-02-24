#pragma once

#include "Event.h"

namespace vz
{
	// Mouse move handle
	class MouseMoveEvent : public Event
	{

	public:
		MouseMoveEvent(float x, float y)
			: m_x(x), m_y(y) {}

#ifdef VZ_DEBUG
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent : " << "(" << m_x << ", " << m_y << ")";
			return ss.str();
		}
#endif

		float GetX() const
		{
			return m_x;
		}

		float GetY() const
		{
			return m_y;
		}

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)
		EVENT_CLASS_TYPE(MouseMoved)

	private:
		float m_x, m_y;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xOffset, float yOffset)
		: m_xOffset(xOffset), m_yOffset(yOffset) {}

#ifdef VZ_DEBUG
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent : " << "(" << m_xOffset << ", " << m_yOffset << ")";
			return ss.str();
		}
#endif

		float GetX() const
		{
			return m_xOffset;
		}

		float GetY() const
		{
			return m_yOffset;
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)


	private:
		float m_xOffset, m_yOffset;
	};

	// Superclass of mouse button event
	class MouseButtonEvent : public Event
	{
	public:
		int GetButton() const { return m_button; }

	protected:
		MouseButtonEvent(int button)
			: m_button(button) {}

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)


		int m_button;
	};

	// Mouse button press handle
	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(int button, int mods)
			: MouseButtonEvent(button), m_modifier(mods) {}

#ifdef VZ_DEBUG
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent : " << m_button;
			return ss.str();
		}
#endif

		int GetModifier() const { return m_modifier; }

		EVENT_CLASS_TYPE(MouseButtonPressed)

	private:
		int m_modifier;
	};

	// Mouse button release handle
	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button)
			: MouseButtonEvent(button) {}

#ifdef VZ_DEBUG
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent : " << m_button;
			return ss.str();
		}
#endif

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}
