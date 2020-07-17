#pragma once
#ifndef SHADER_H

#define SHADER_H

#include <glad/glad.h>
#include <string>

#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	void use();

	void SetBool(const std::string  &name, bool value) const;//const在后，表示为只读函数，不允许修改类的数据成员
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	unsigned int ID;


private:

};
Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	  // 1、从文件路径中获取着色器程序
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	//保证ifstream可抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		//读取文件流到数据流当中 
		
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();

		fragmentCode = fShaderStream.str();
	}
	catch ( std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULY_READ" << std::endl;
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	//2、编译着色器
	unsigned int vertexShader, fragmentShader;

	int success;
	char infoLog[512];

	//build and compile shader program
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);

	glCompileShader(vertexShader);
	//check error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::Shader::VertexShader::compilation_failed\n" << infoLog << std::endl;
	}

	//创建片元着色器
	 fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);

	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::Shader::FragmentShader::compilation_failed\n" << infoLog << std::endl;
	}

	//创建着色器程序
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::shader::program::linking_failed\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}
void Shader::SetBool(const std::string& name, bool value)const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value)const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat (const std::string& name, float value)const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
#endif // !SHADER_H
