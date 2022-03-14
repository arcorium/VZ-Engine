#pragma once

#include <glm/glm.hpp>

namespace vz
{
	//class VZ_API ICamera
	//{
	//public:

	//	virtual ~ICamera() = default;

	//	virtual const glm::mat4& GetView() const = 0;
	//	virtual const glm::mat4& GetProjection() const = 0;
	//	virtual const glm::mat4& GetViewProjection() const = 0;

	//	virtual void SetPosition(const glm::vec3& pos) = 0;
	//	virtual const glm::vec3& GetPosition() const = 0;

	//	/**
	//	 * \brief Update the camera view matrix
	//	 */
	//	virtual void UpdateCamera() = 0;
	//};

	class OrthographicCamera
	{
	public:
		OrthographicCamera();
		OrthographicCamera(float left, float right, float bottom, float top, float near_ = -1.0f, float far_ = 1.0f);
		//OrthographicCamera(float left, float right, float bottom, float top, const glm::vec3& position = glm::vec3{0.0f});

		~OrthographicCamera();

		const glm::mat4& GetView() const;
		const glm::mat4& GetProjection() const;
		const glm::mat4& GetViewProjection() const;

		void SetPosition(const glm::vec3& pos);
		const glm::vec3& GetPosition() const;

		void SetRotation(float rotation);
		float GetRotation() const;

	private:
		void UpdateCamera();

	private:
		glm::mat4 m_projection;
		glm::mat4 m_view;
		glm::mat4 m_viewProjection;

		glm::vec3 m_position;
		float m_rotation;	// Z Axis rotation
	};
}