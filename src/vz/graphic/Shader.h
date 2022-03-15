#pragma once

typedef unsigned int GLenum;

namespace vz
{
    class VZ_API IShader
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

        virtual ~IShader() = default;

        virtual void Load(const ShaderInfo& shaderInfo) = 0;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static void SetPath(const std::string& path, bool append = false);

        // Temporary
        // Casting into derived class of Shader
        template<vz::derived<IShader> T>
        T* CastTo();

        static IShader* Create(const std::string& name);

        static std::shared_ptr<IShader> CreateShared(const std::string& name);

    protected:
        inline static std::string s_filepath = std::filesystem::current_path().string() + '\\';
    };

    std::string ReadFile(const std::string& path);

    template <vz::derived<IShader> T>
    T* IShader::CastTo()
    {
        return static_cast<T*>(this);
    }
}
