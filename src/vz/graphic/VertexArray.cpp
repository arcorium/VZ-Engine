#include "vzpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace vz
{
	IVertexArray* IVertexArray::Create()
	{
		switch (Renderer::CurrentAPI())
		{
		case IRendererAPI::API::NONE: break;
		case IRendererAPI::API::OPENGL: return new OpenGLVertexArray{};
		case IRendererAPI::API::DIRECTX: break;
		case IRendererAPI::API::VULKAN: break;
		default: ;
		}

		VZ_CORE_ASSERT(false, "the graphic is not supported!");
		return nullptr;
	}

	std::shared_ptr<IVertexArray> IVertexArray::CreateShared()
	{
		switch (Renderer::CurrentAPI())
		{
		case IRendererAPI::API::NONE: break;
		case IRendererAPI::API::OPENGL: return std::make_shared<OpenGLVertexArray>();
		case IRendererAPI::API::DIRECTX: break;
		case IRendererAPI::API::VULKAN: break;
		default:;
		}

		VZ_CORE_ASSERT(false, "the graphic is not supported!");
		return nullptr;
	}
}
