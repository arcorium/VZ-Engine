#include "vzpch.h"
#include "Shader.h"

#include <glm/gtc/type_ptr.hpp>

#include "glad/glad.h"

namespace vz
{
    Shader::Shader(const std::string& name, const ShaderInfo& shaderInfo)
        : m_id(glCreateProgram()), m_name(name), m_info(shaderInfo)
    {
        Load(shaderInfo);
    }

    Shader::Shader(const std::string& name)
        : m_id(glCreateProgram()), m_name(name)
    {
    }

    Shader::~Shader()
    {
        Cleanup();
    }

    void Shader::Load(const ShaderInfo& shaderInfo)
    {
        m_info = shaderInfo;
        Init();
    }

    void Shader::Bind()
    {
        glUseProgram(m_id);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    int Shader::ProcessCache(const std::string& name)
    {
        if (!m_cache.contains(name))
        {
            int location = glGetUniformLocation(m_id, name.c_str());

            if (location == -1)
            {
                m_falseCache[name] = true;
                if (m_falseCache[name])
                {
                    VZ_WARN("failed to regiter uniform with name {}", name);

                    m_falseCache[name] = false;
                }

                return false;
            }

            m_cache[name] = location;

            VZ_INFO("regiter uniform with name {} in {}", name, location);
        }

        return m_cache[name];
    }

    void Shader::SetPath(const std::string& path, bool append)
    {
        if (append)
            s_filepath += path;
        else
            s_filepath = path;
    }

    void Shader::Init()
    {

        unsigned vertex = 0,
            tenselControl = 0,
            tenselEvaluation = 0,
            geometry = 0,
            compute = 0,
            fragment = 0;

        // Compile Shader

        if (!m_info.Vertex.empty())
        {
            m_info.Vertex = ReadFile(s_filepath + m_info.Vertex);
            vertex = Compile(m_info.Vertex, GL_VERTEX_SHADER);

            // Attach Shader
            glAttachShader(m_id, vertex);
        }
        if (!m_info.TenselControl.empty())
        {
            m_info.TenselControl = ReadFile(s_filepath + m_info.TenselControl);
            tenselControl = Compile(m_info.TenselControl, GL_TESS_CONTROL_SHADER);

            // Attach Shader
            glAttachShader(m_id, tenselControl);
        }
        if (!m_info.TenselEvaluation.empty())
        {
            m_info.TenselEvaluation = ReadFile(s_filepath + m_info.TenselEvaluation);
            tenselEvaluation = Compile(m_info.TenselEvaluation, GL_TESS_EVALUATION_SHADER);

            // Attach Shader
            glAttachShader(m_id, tenselEvaluation);
        }
        if (!m_info.Geometry.empty())
        {
            m_info.Geometry = ReadFile(s_filepath + m_info.Geometry);
            geometry = Compile(m_info.Geometry, GL_GEOMETRY_SHADER);

            // Attach Shader
            glAttachShader(m_id, geometry);
        }
        if (!m_info.Compute.empty())
        {
            m_info.Compute = ReadFile(s_filepath + m_info.Compute);
            compute = Compile(m_info.Compute, GL_COMPUTE_SHADER);

            // Attach Shader
            glAttachShader(m_id, compute);
        }
        if (!m_info.Fragment.empty())
        {
            m_info.Fragment = ReadFile(s_filepath + m_info.Fragment);
            fragment = Compile(m_info.Fragment, GL_FRAGMENT_SHADER);

            // Attach Shader
            glAttachShader(m_id, fragment);
        }

        // Linking
        glLinkProgram(m_id);

        // Error checking
        int status;
        glGetProgramiv(m_id, GL_LINK_STATUS, &status);

        if (!status)
        {
            char log[512];
            glGetProgramInfoLog(m_id, 512, nullptr, log);

            VZ_WARN("{}", log);

            // Failed to link shader into program
            glDeleteProgram(m_id);
        }

        if (vertex)
            glDeleteShader(vertex);
        if (tenselControl)
            glDeleteShader(tenselControl);
        if (tenselEvaluation)
            glDeleteShader(tenselEvaluation);
        if (geometry)
            glDeleteShader(geometry);
        if (compute)
            glDeleteShader(compute);
        if (fragment)
            glDeleteShader(fragment);

    }

    void Shader::Cleanup()
    {
        glDeleteProgram(m_id);
    }

    unsigned Shader::Compile(const std::string& src, GLenum type)
    {

        unsigned shader = glCreateShader(type);
        const char* data = src.data();
        glShaderSource(shader, 1, &data, nullptr);
        glCompileShader(shader);

        int status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            char log[512];
            glGetShaderInfoLog(shader, 512, nullptr, log);
            std::string header;
            switch (type)
            {
            case GL_VERTEX_SHADER:
                header = m_name + "-V";
                break;
            case GL_FRAGMENT_SHADER:
                header = m_name + "-F";
                break;
            case GL_GEOMETRY_SHADER:
                header = m_name + "G";
                break;
            case GL_TESS_CONTROL_SHADER:
                header = m_name + "-TC";
                break;
            case GL_TESS_EVALUATION_SHADER:
                header = m_name + "-TE";
                break;
            case GL_COMPUTE_SHADER:
                header = m_name + "-C";
                break;
            default:
                header = m_name;
            }

            VZ_WARN("{}", log);

            glDeleteShader(shader);
            return 0;
        }

        return shader;
    }

    void Shader::SetUniform(const std::string& name, int val)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform1i(m_id, location, val);
    }

    void Shader::SetUniform(const std::string& name, bool value)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform1i(m_id, location, static_cast<int>(value));
    }

    void Shader::SetUniform(const std::string& name, unsigned value)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform1ui(m_id, location, value);
    }

    void Shader::SetUniform(const std::string& name, float value)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform1f(m_id, location, value);
    }

    void Shader::SetUniform(const std::string& name, double value)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform1d(m_id, location, value);
    }

    void Shader::SetUniform(const std::string& name, glm::vec3 vec3)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform3fv(m_id, location, 1, glm::value_ptr(vec3));
    }

    void Shader::SetUniform(const std::string& name, glm::vec2 vec2)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform2fv(m_id, location, 1, glm::value_ptr(vec2));
    }

    void Shader::SetUniform(const std::string& name, float value1, float value2, float value3)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform3f(m_id, location, value1, value2, value3);
    }

    void Shader::SetUniform(const std::string& name, double value1, double value2, double value3)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform3d(m_id, location, value1, value2, value3);
    }

    void Shader::SetUniform(const std::string& name, glm::mat4 mat4)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform4fv(m_id, location, 1, glm::value_ptr(mat4));
    }

    void Shader::SetUniform(const std::string& name, float value1, float value2, float value3, float value4)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform4f(m_id, location, value1, value2, value3, value4);
    }

    void Shader::SetUniform(const std::string& name, double value1, double value2, double value3, double value4)
    {
        if (const int location = ProcessCache(name) >= 0)
            glProgramUniform4d(m_id, location, value1, value2, value3, value4);
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