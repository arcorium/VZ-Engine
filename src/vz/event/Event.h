#pragma once
#include "vzpch.h"

#include "vz/Core.h"

namespace vz
{

	// Currently using blocking event, that will block or pause engine system when event is occur

	// Kind or Type of enum
	enum class EventType	// Enum class doesn't implicitly converted into int but enum does
	{
		None = 0,
		// Window
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// Application
		AppTick, AppUpdate, AppRender,
		// Key
		KeyPressed, KeyReleased,
		// Mouse
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};


	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),		// 1
		EventCategoryInput			= BIT(1),		// 2
		EventCategoryKeyboard		= BIT(2),		// 4
		EventCategoryMouse			= BIT(3),		// 8
		EventCategoryMouseButton	= BIT(4)		// C

	};

	// Set the type of the event and override all function needed as virtual
	#define EVENT_CLASS_TYPE(type)\
								static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

	// Set the category of the event and override getter to return those category
	#define EVENT_CLASS_CATEGORY(cat)	int GetCategoryFlags() const override { return cat; }

	/**
	 * \brief Interface class Event
	 */
	class VZ_API Event
	{
		friend class EventDispatcher;	// Friend class allowed to access private member

	public:
		/**
		 * \brief Get event type
		 * \return EventType enum 
		 */
		virtual EventType GetEventType() const = 0;

		/**
		 * \brief Get Event name
		 * \return event name
		 */
		virtual const char* GetName() const = 0;

		/**
		 * \brief Get category
		 * \return Category flags on bit power by 2
		 */
		virtual int GetCategoryFlags() const = 0;

		/**
		 * \brief Returning string for the event that by default is return event's name
		 * \return string 
		 */
		virtual std::string ToString() const { return GetName(); }

		/**
		 * \brief Checking if the category is on EventCategory
		 * \param category category to look at
		 * \return true if the category is on EventCategory enum
		 */
		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}


	protected:

		bool m_handled = false;		// To make know if the event occurred is already handled by system like button or not.
	};

	// Dispatching event base on their type and category
	class EventDispatcher
	{

		template <typename T>
		using EventFn = std::function<bool(T&)>;	// The function will be "bool fn(T&)" and not implemented yet

	public:
		EventDispatcher(Event& ev) : m_event(ev) {}


		/**
		 * \brief Dispatching event by the type and function defined on parameter
		 * \tparam T subclass of Event
		 * \param fn function will be passed
		 * \return true if event is successfully dispatched and false otherwise
		 */
		template <typename T>
		bool Dispatch(EventFn<T> fn)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				// casting event into the correspondent type (subclass) 
				m_event.m_handled = fn(*static_cast<T*>(&m_event));	// Using & instead of the value itself, because member variable is only underlying variable and not actual variable that holds data

				return true;
			}

			return false;
		}

	private:
		// Underlying variable
		Event &m_event;
	};

	// Overloading
	inline std::ostream& operator<<(std::ostream& os, const Event& ev)
	{
		return os << ev.ToString();
	}
}