#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include <OGL1/Shaders/Shaders.h>
#include <OGL1/Renderer/Renderer.h>


Shaders::Shaders(const std::string& filePath)
	:m_FilePath(filePath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_RendererID = CreateShader(source.SPS_VertexSource, source.SPS_FragmentSource);
}

Shaders::~Shaders()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shaders::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shaders::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shaders::SetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shaders::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shaders::SetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shaders::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shaders::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}

	m_UniformLocationCache[name] = location;

	return location;
}


unsigned int Shaders::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vertShader = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

unsigned int Shaders::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		int lenght;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
		char* message = (char*)alloca(lenght * sizeof(char));
		glGetShaderInfoLog(id, lenght, &lenght, message);

		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);

		return 0;
	}

	return id;
}

ShaderProgramSource Shaders::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	enum class ShaderType
	{
		ST_NONE = -1,
		ST_VERTEX = 0,
		ST_FRAGMENT = 1
	};

	std::string line;
	std::stringstream stringStream[2];

	ShaderType shaderType = ShaderType::ST_NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("Vert") != std::string::npos)
			{
				shaderType = ShaderType::ST_VERTEX;
			}
			else if (line.find("Frag") != std::string::npos)
			{
				shaderType = ShaderType::ST_FRAGMENT;
			}
		}
		else
		{
			stringStream[(int)shaderType] << line << '\n';
		}
	}

	return { stringStream[0].str(),stringStream[1].str() };
}
