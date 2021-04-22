#pragma once
#include "glad/glad.h"

#include <string>
#include <unordered_map>

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererId;
	std::unordered_map<std::string, unsigned int> m_UniformCache;
	const ShaderSource ParseShaderSource(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
public:
	Shader();
	~Shader();
	unsigned int  CreateShader(std::string filepath);
	void Bind() const;
	void Unbind() const;
	void SetUniformInt(std::string name, int value);
	void SetUniformFloat(std::string name, float value);
	void SetUniformVec3(std::string name, float x, float y, float z);
	void SetUniformVec4(std::string name, float x, float y, float z, float w);
	int GetUniformLocation(unsigned int program,std::string name);

};