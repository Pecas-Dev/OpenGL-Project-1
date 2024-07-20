#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>


struct ShaderProgramSource
{
	std::string SPS_VertexSource;
	std::string SPS_FragmentSource;
};


class Shaders
{
private:
	unsigned int m_RendererID;

	std::string m_FilePath;

	std::unordered_map<std::string, int> m_UniformLocationCache;

	int GetUniformLocation(const std::string& name);

	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	ShaderProgramSource ParseShader(const std::string& filePath);

public:
	Shaders(const std::string& filePath);
	~Shaders();

	void Bind() const;
	void Unbind() const;

	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

	void SetUniform1i(const std::string& name, int value);

	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};
