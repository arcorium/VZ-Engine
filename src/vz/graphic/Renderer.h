#pragma once
#include "RendererAPI.h"
#include "Shader.h"
#include "../Camera.h"

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

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(std::shared_ptr<IShader>& shader, const std::shared_ptr<IVertexArray>& vertexArray, const glm::mat4& transform = glm::mat4{1.0f});

	private:
		static IRendererAPI::API s_api;
	};
}
