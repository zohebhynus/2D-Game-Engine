/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Purpose: Main file
Language: C
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 11/29/2017
- End Header --------------------------------------------------------*/

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow *window);

float x_pos=0.0f;
float y_pos=0.0f;
float rot = 0.0f;
bool a = true;
int action;


const char *vertex_shader_source = "#version 400 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"

"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"uniform mat4 transform;\n"

"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"	ourColor = aColor;\n"
"	TexCoord = vec2(aTexCoord.x, aTexCoord.y);"
"}\0";

const char *fragment_shader_source = "#version 400 core\n"
"out vec4 FragColor;\n"

"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"

"uniform sampler2D ourTexture;\n"
"uniform bool foo;\n"
"void main()\n"
"{\n"
"if(foo)\n"
"{\n"
"   FragColor = texture(ourTexture, TexCoord);\n"
"}\n"
"else\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n"
"}\n\0";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	


	// create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Sonic", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad : loading opengl function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	std::cout << "-----------MILESTONE 4--------------\n WASD - to move\n Q E - to rotate \n spacebar - to change between color and texture mode(caution:a little bit funky)\n" << std::endl;
	std::cout << "CURRENT MODE : Texture\n" << std::endl;
	//build vertex shader
	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	//build fragment shader
	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	//linking the shaders
	unsigned int shader_program;
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	//vertex data
	float vertices[] = {
		// positions          // colors           // texture coords
		0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		0.2f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.2f,  0.2f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//texture
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//loading image for texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("sonic.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glUseProgram(shader_program);
	glUniform1i(glGetUniformLocation(shader_program, "texture"), 0);
	
	


	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		process_input(window);

		//render commands
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0); 
		glBindTexture(GL_TEXTURE_2D, texture);

		//create transformation
		glm::mat4 trans;
		glm::vec3 move;
		trans = glm::translate(trans, glm::vec3(x_pos, y_pos, 0.0f));
		trans = glm::rotate(trans, glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));

		glUseProgram(shader_program);
		unsigned int transformLoc = glGetUniformLocation(shader_program, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glUniform1i(glGetUniformLocation(shader_program, "foo"), a);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

//input queries
void process_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		y_pos += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		y_pos -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		x_pos -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		x_pos += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		rot += 5.0f;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		rot -= 5.0f;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
			
		if (a)
		{
			a = false;
			std::cout << "CURRENT MODE : Color\n" << std::endl;
		}
		else
		{
			a = true;
			std::cout << "CURRENT MODE : Texture\n" << std::endl;
		}
		
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
