#pragma once
#include <glm/glm.hpp>

typedef unsigned int GLenum;

namespace vz
{
    class Shader
    {
    public:
        struct ShaderInfo
        {
            std::string Vertex;
            std::string TenselControl;
            std::string TenselEvaluation;
            std::string Geometry;
            std::string Compute;
            std::string Fragment;
        };

        Shader(const std::string& name, const ShaderInfo& shaderInfo);
        Shader(const std::string& name);
        ~Shader();

        void Load(const ShaderInfo& shaderInfo);

        void Bind();
        void Unbind();

        void SetUniform(const std::string& name, bool value);
        void SetUniform(const std::string& name, int value);
        void SetUniform(const std::string& name, unsigned value);
        void SetUniform(const std::string& name, float value);
        void SetUniform(const std::string& name, double value);
        void SetUniform(const std::string& name, glm::vec3 vec3);
        void SetUniform(const std::string& name, glm::vec2 vec2);
        void SetUniform(const std::string& name, float value1, float value2, float value3);
        void SetUniform(const std::string& name, double value1, double value2, double value3);
        void SetUniform(const std::string& name, glm::mat4 mat4);
        void SetUniform(const std::string& name, float value1, float value2, float value3, float value4);
        void SetUniform(const std::string& name, double value1, double value2, double value3, double value4);

        int ProcessCache(const std::string& name);

        static void SetPath(const std::string& path, bool append = false);

    private:
        void Init();
        void Cleanup();
        unsigned Compile(const std::string& src, GLenum type);

    private:
        inline static std::string s_filepath = std::filesystem::current_path().string() + '\\';

        unsigned m_id;
        std::string m_name;
        ShaderInfo m_info;

        std::unordered_map<std::string, int> m_cache;
        std::unordered_map<std::string, bool> m_falseCache;
    };

    std::string ReadFile(const std::string& path);
}
