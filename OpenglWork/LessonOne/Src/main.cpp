


#include <iostream>

#include <fstream>
#include <sstream>
#include <string>
#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"
#include  <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, 800, 600);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Cotangents", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;

	}

	float vertices[] = {
		 0.5f, 0.5f, 0.0f,	  0.0f,0.0f,   // 右上角
		 0.5f, -0.5f, 0.0f,  1.0f,0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f,  1.0f,1.0f,// 左下角
		-0.5f, 0.5f, 0.0f,   0.0f,1.0f // 左上角
	};

	float vertices2[] = {
		 0.5f, 0.5f, 0.0f,   // 右上角
		-0.5f, 0.5f, 0.0f ,    // 左上角
		0.0f, 1.0f, 0.0f,  // 顶点
		
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3,
	}; 

	unsigned int indices2[] = {
		0,1,2
	};
	
	VertexArray vao;
	VertexArray vao1;
	VertexBuffer vb(vertices, 4 * 5 * sizeof(float));
	IndexBuffer ebo(indices, 6);

	
	//描述顶点的排列方式
	VertexBufferLayout layout;
	//每个顶点的数量
	layout.Push<float>(3);
	layout.Push<float>(2);
	vao.AddBuffer(vb, layout);
	ebo.Bind();

	vb.Unbind();
	Shader shader;
	unsigned int program = shader.CreateShader("shader/shader01.shader");
	shader.Bind();

	shader.SetUniformVec4("u_Color", 0.5f, 0.5f, 0.5f, 1.0f);

	Texture texture2D("Resources/wall.jpg");
	texture2D.Bind(0);
	shader.SetUniformInt("tex",0);
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		vao.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}


