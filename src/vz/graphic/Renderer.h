#pragma once
#include "RendererAPI.h"

namespace vz
{
	class VZ_API RenderCommand
	{
	public:

		static void SetClearColor(const glm::vec4& color);
		static void Clear(ClearFlag flags);

		static void DrawIndexed(const std::shared_ptr<IVertexArray>& vertexArray);

	private:
		static IRendererAPI* s_rendererAPI;
	};

	class VZ_API Renderer
	{
	public:
		static IRendererAPI::API CurrentAPI();

		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<IVertexArray>& vertexArray);

	private:
		static IRendererAPI::API s_api;
	};
}
