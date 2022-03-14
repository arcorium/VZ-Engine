#include "vzpch.h"
#include "Renderer.h"

#include "OpenGL/OpenGLRendererAPI.h"

#include <glm/gtc/type_ptr.hpp>


namespace vz
{
	// Renderer API static member
	IRendererAPI::API Renderer::s_api = IRendererAPI::API::OPENGL;

	// RendererAPI static member
	IRendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI{};

	// RenderCommand


	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_rendererAPI->SetClearColor(color);
	}

	void RenderCommand::Clear(ClearFlag flags)
	{
		s_rendererAPI->Clear(flags);
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<IVertexArray>& vertexArray)
	{
		s_rendererAPI->DrawIndexed(vertexArray);
	}


	// Renderer

	namespace
	{
		bool isEnd = true;
		const glm::mat4* viewProjectionMatrix;
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		viewProjectionMatrix = &camera.GetViewProjection();
	}

	void Renderer::EndScene()
	{
		isEnd = true;
	}

	IRendererAPI::API Renderer::CurrentAPI()
	{
		return s_api;
	}

	void Renderer::Submit(std::shared_ptr<Shader>& shader, const std::shared_ptr<IVertexArray>& vertexArray)
	{
		if (isEnd)
		{
			shader->SetUniform("u_viewProjection", *viewProjectionMatrix);
			isEnd = false;
		}

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
