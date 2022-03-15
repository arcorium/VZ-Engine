#include "vzpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "vz/graphic/OpenGL/OpenGLShader.h"

namespace vz
{
    void IShader::SetPath(const std::string& path, bool append)
    {
        if (append)
            s_filepath += path;
        else
            s_filepath = path;
    }

    IShader* IShader::Create(const std::string& name)
    {
        switch (Renderer::CurrentAPI())
        {
        case IRendererAPI::API::NONE: break;
        case IRendererAPI::API::OPENGL:	return new OpenGLShader{name};
        case IRendererAPI::API::DIRECTX: break;
        case IRendererAPI::API::VULKAN: break;
        default:;
        }

        VZ_CORE_ASSERT(false, "No renderer API being used!");
        return nullptr;
    }

    std::shared_ptr<IShader> IShader::CreateShared(const std::string& name)
    {
        switch (Renderer::CurrentAPI())
        {
        case IRendererAPI::API::NONE: break;
        case IRendererAPI::API::OPENGL:	return std::make_shared<OpenGLShader>(name);
        case IRendererAPI::API::DIRECTX: break;
        case IRendererAPI::API::VULKAN: break;
        default:;
        }

        VZ_CORE_ASSERT(false, "No renderer API being used!");
        return nullptr;
    }
}

std::string vz::ReadFile(const std::string& path)
{
    std::fstream stream{ path };

    std::string data;

    if (stream.is_open())
    {
        std::string line;

        while (std::getline(stream, line))
        {
            data += line + '\n';
        }
    }

    return data;
}