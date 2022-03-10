#pragma once
#include "VertexArray.h"
#include "glm/vec4.hpp"

namespace vz
{

	enum ClearFlag : uint8_t
	{
		COLOR = BIT(1),
		DEPTH = BIT(2),
		STENCIL = BIT(3),
	};

	class IRendererAPI
	{
	public:
		enum class API
		{
			NONE,
			OPENGL,
			DIRECTX,
			VULKAN
		};

		virtual ~IRendererAPI() = default;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear(ClearFlag flags) = 0;

		virtual void DrawIndexed(const std::shared_ptr<IVertexArray>& vertexArray) = 0;
	};


	inline ClearFlag operator|(const ClearFlag& lhs, const ClearFlag& rhs)
	{
		return static_cast<ClearFlag>(SCAST(uint8_t, lhs) | SCAST(uint8_t, rhs));
	}
}
