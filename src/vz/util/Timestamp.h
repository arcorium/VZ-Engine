#pragma once
#include "vzpch.h"

#include <GLFW/glfw3.h>

namespace vz
{
	
	class Time
	{

	public:
		enum Type : uint32_t
		{
			S = 1,				// Second
			MS = 1000,			// Millisecond
			NS = 1000000000,	// Nanosecond
		};

	public:
		Time() : m_time(static_cast<float>(glfwGetTime())) {}
		Time(float time) : m_time(time) {}

		/*
		 * \brief Setting time in here to get distance to Stop method
		 */
		void Start() { m_time = static_cast<float>(glfwGetTime()); }

		/*
		 * \brief Stop time here and get the distance or delta time form Start to Stop
		 */
		void Stop() { m_distance = static_cast<float>(glfwGetTime()); m_distance = m_distance - m_time; }

		void CalculateDelta() { m_lastTime = static_cast<float>(glfwGetTime()); m_distance = m_lastTime - m_time; m_time = m_lastTime; }

		operator float() const { return m_time; }

		/**
		 * \brief Get delta time in second, millisecond, nanosecond or get the value times to delta time.
		 * \tparam T type should be integer or floating point
		 * \param rhs value to calculate with
		 * \return value in float (no matter what type passed
		 */
		template <typename T>
		float operator()(const T& rhs)
		{
			return rhs * m_distance;
		}
	private:
		float m_time;
		float m_lastTime;
		float m_distance = 0.0f;	// Delta time in second
	};

}