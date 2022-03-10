#include "vzpch.h"
#include "Renderer.h"

#include "OpenGL/OpenGLRendererAPI.h"


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

	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	IRendererAPI::API Renderer::CurrentAPI()
	{
		return s_api;
	}

	void Renderer::Submit(const std::shared_ptr<IVertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
