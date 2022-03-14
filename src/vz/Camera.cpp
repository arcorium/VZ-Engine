#include "vzpch.h"
#include "Camera.h"

#include <glm/ext/matrix_projection.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace vz
{
	OrthographicCamera::OrthographicCamera()
		: m_projection(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)), m_view(1.0f), m_position(0.0f), m_rotation(0.0f)
	{
		UpdateCamera();
	}

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near_, float far_)
		: m_projection(glm::ortho(left, right, bottom, top, near_, far_)), m_view(1.0f), m_position(0.0f), m_rotation(0.0f)
	{
		UpdateCamera();
	}

	//OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, const glm::vec3& position)
	//	: m_projection(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_view(1.0f), m_position(position), m_rotation(0.0f)
	//{
	//	UpdateCamera();
	//}

	OrthographicCamera::~OrthographicCamera()
	{
	}

	const glm::mat4& OrthographicCamera::GetView() const
	{
		return m_view;
	}

	const glm::mat4& OrthographicCamera::GetProjection() const
	{
		return m_projection;
	}

	const glm::mat4& OrthographicCamera::GetViewProjection() const
	{
		return m_viewProjection;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& pos)
	{
		m_position = pos;
		UpdateCamera();
	}

	const glm::vec3& OrthographicCamera::GetPosition() const
	{
		return m_position;
	}

	void OrthographicCamera::UpdateCamera()
	{
		// Calculate transform
		// Translation
		glm::mat4 transform = glm::translate(glm::mat4{ 1.0f }, m_position);
		// Rotation
		transform = glm::rotate(transform, glm::radians(m_rotation), { 0.0f, 0.0f, 1.0f });

		// Update the view
		m_view = glm::inverse(transform);

		// Update the projection
		m_viewProjection = m_projection * m_view;	// OpenGL uses column major matrix
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_rotation = rotation;
		UpdateCamera();
	}

	float OrthographicCamera::GetRotation() const
	{
		return m_rotation;
	}
}
