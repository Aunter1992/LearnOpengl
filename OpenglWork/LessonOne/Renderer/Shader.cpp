#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader()
	:m_RendererId(0)
{
	
}
Shader::~Shader()
{
	glDeleteProgram(m_RendererId);
}
const ShaderSource  Shader::ParseShaderSource(const std::string& filepath)
{
	std::ifstream fs(filepath);
	std::string line;
	std::stringstream ss[2];
	enum  class ShaderType
	{
		None = -1, Vertex = 0, Fragment = 1
	};
	ShaderType shaderType;
	while (getline(fs, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				shaderType = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				shaderType = ShaderType::Fragment;
			}
		}
		else
		{
			ss[(int)shaderType] << line << "\n";
		}
	}
	return { ss[0].str(),ss[1].str() };
}

unsigned int  Shader::CreateShader(std::string filepath)
{
	ShaderSource source = ParseShaderSource(filepath);

	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, source.vertexSource);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, source.fragmentSource);

	m_RendererId = glCreateProgram();
	glAttachShader(m_RendererId, vertex);
	glAttachShader(m_RendererId, fragment);

	glLinkProgram(m_RendererId);
	glValidateProgram(m_RendererId);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return m_RendererId;

}

unsigned int  Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl;
		std::cout << message << std::endl;
	}
	return id;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

 int Shader::GetUniformLocation(unsigned int program, std::string name)
{
	if (m_UniformCache.find(name) != m_UniformCache.end())
	{
		return m_UniformCache[name];
	}
    auto  id=glGetUniformLocation(program, name.c_str());
	m_UniformCache.insert({name,id});
	return id;
}
void Shader::SetUniformInt(std::string name, int value)
{
	int location = GetUniformLocation(m_RendererId, name);
	glUniform1i(location, value);
}
void Shader::SetUniformFloat(std::string name,float value)
{
	int location = GetUniformLocation(m_RendererId, name);
	glUniform1f(location, value);
}
void Shader::SetUniformVec3(std::string name, float x, float y, float z)
{
	int location = GetUniformLocation(m_RendererId, name);
	glUniform3f(location, x,y,z);
}
void Shader::SetUniformVec4(std::string name, float x, float y, float z, float w)
{
	int location = GetUniformLocation(m_RendererId, name);
	glUniform4f(location, x, y, z,w);
}