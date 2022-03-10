#include "vzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "OpenGL/OpenGLBuffer.h"

namespace vz
{
	IVertexBuffer* IVertexBuffer::Create(unsigned size, const void* data)
	{
		switch (Renderer::CurrentAPI())
		{
		case IRendererAPI::API::NONE: break;
		case IRendererAPI::API::OPENGL:	return new OpenGLVertexBuffer{size, data};
		case IRendererAPI::API::DIRECTX: break;
		case IRendererAPI::API::VULKAN: break;
		default: ;
		}

		VZ_CORE_ASSERT(false, "No renderer API being used!");
		return nullptr;
	}

	std::shared_ptr<IVertexBuffer> IVertexBuffer::CreateShared(unsigned size, const void* data)
	{
		switch (Renderer::CurrentAPI())
		{
		case IRendererAPI::API::NONE: break;
		case IRendererAPI::API::OPENGL:	return std::make_shared<OpenGLVertexBuffer>(size, data);
		case IRendererAPI::API::DIRECTX: break;
		case IRendererAPI::API::VULKAN: break;
		default:;
		}

		VZ_CORE_ASSERT(false, "No renderer API being used!");
		return nullptr;
	}

	IIndexBuffer* IIndexBuffer::Create(unsigned size, const void* data)
	{
		switch (Renderer::CurrentAPI())
		{
		case IRendererAPI::API::NONE: break;
		case IRendererAPI::API::OPENGL:	return new OpenGLIndexBuffer{ size, data };
		case IRendererAPI::API::DIRECTX: break;
		case IRendererAPI::API::VULKAN: break;
		default:;
		}

		VZ_CORE_ASSERT(false, "No renderer API being used!");
		return nullptr;
	}

	std::shared_ptr<IIndexBuffer> IIndexBuffer::CreateShared(unsigned size, const void* data)
	{
		switch (Renderer::CurrentAPI())
		{
		case IRendererAPI::API::NONE: break;
		case IRendererAPI::API::OPENGL:	return std::make_shared<OpenGLIndexBuffer>(size, data);
		case IRendererAPI::API::DIRECTX: break;
		case IRendererAPI::API::VULKAN: break;
		default:;
		}

		VZ_CORE_ASSERT(false, "No renderer API being used!");
		return nullptr;
	}

}