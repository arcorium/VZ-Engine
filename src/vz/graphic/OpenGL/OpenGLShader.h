#pragma once
#include "vz/graphic/Shader.h"
#include <glm/glm.hpp>

namespace vz
{
	class VZ_API OpenGLShader : public IShader
	{
	public:
		OpenGLShader(const std::string& name, const ShaderInfo& shaderInfo);
		OpenGLShader(const std::string& name);

		~OpenGLShader() override;

		void Load(const ShaderInfo& shaderInfo) override;
		void Bind() override;
		void Unbind() override;

		void SetUniform(const std::string& name, bool value);
		void SetUniform(const std::string& name, int value);
		void SetUniform(const std::string& name, unsigned value);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, double value);
		void SetUniform(const std::string& name, glm::vec3 vec3);
		void SetUniform(const std::string& name, glm::vec2 vec2);
		void SetUniform(const std::string& name, float value1, float value2, float value3);
		void SetUniform(const std::string& name, double value1, double value2, double value3);
		void SetUniform(const std::string& name, const glm::mat4& mat4);
		void SetUniform(const std::string& name, float value1, float value2, float value3, float value4);
		void SetUniform(const std::string& name, double value1, double value2, double value3, double value4);

		bool FoundInCache(const std::string& name);

	private:
		void Init();
		void Cleanup();
		unsigned Compile(const std::string& src, GLenum type);

	private:
		unsigned m_id;
		std::string m_name;
		ShaderInfo m_info;

		std::unordered_map<std::string, int> m_cache;
		std::unordered_map<std::string, bool> m_falseCache;
	};
}
