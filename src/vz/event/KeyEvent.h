#pragma once
#include "Event.h"

namespace vz
{
	/**
	 * \brief Keyboard Event super class
	 */
	class VZ_API KeyEvent : Event
	{

	public:
		/**
		 * \brief Get keyboard keycode
		 * \return keycode
		 */
		int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategory::EventCategoryInput | EventCategory::EventCategoryKeyboard)
	protected:
		/**
		 * \brief Constructing by defining the keycode
		 * \param keycode keycode
		 */
		KeyEvent(int keycode) : m_keyCode(keycode) {}

		// keyboard keycode
		int m_keyCode;
	};

	/**
	 * \brief Keyboard Event Press handle
	 */
	class VZ_API KeyPressEvent : public KeyEvent
	{
	public:
		/**
		 * \brief Constructing by defining keycode and repeatcount
		 * \param keycode 
		 * \param repeatCount 
		 */
		KeyPressEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_repeatCount(repeatCount) {}

		/**
		 * \brief Get Total Repeated key count
		 * \return total repeated key count
		 */
		int GetRepeatCount() const { return m_repeatCount; }

		#ifdef VZ_DEBUG
		std::string ToString() const override
		{

			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << ")";
			return ss.str();
		}
		#endif

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		// total key repeat
		int m_repeatCount;
	};

	/**
	 * \brief Keyboard event release handle
	 */
	class VZ_API KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keycode)
			: KeyEvent(keycode) {}

		#ifdef VZ_DEBUG
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent : " << m_keyCode;

			return ss.str();
		}
		#endif

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
