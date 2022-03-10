#pragma once
#include "vz/graphic/RendererAPI.h"

namespace vz
{
	class VZ_API OpenGLRendererAPI : public IRendererAPI
	{
	public:
		OpenGLRendererAPI() = default;
		~OpenGLRendererAPI() override = default;

		void SetClearColor(const glm::vec4& color) override;
		void Clear(ClearFlag flags) override;
		void DrawIndexed(const std::shared_ptr<IVertexArray>& vertexArray) override;
	};
}
