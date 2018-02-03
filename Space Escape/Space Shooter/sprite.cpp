/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "Sprite.h"
#include "stdio.h"
#include "..\SDL2.0 Lib\include\SDL_surface.h" 
#include "resource_manager.h"
#include <cstring>
#include <string>


extern resource_manager *p_rm;

sprite::sprite() : component(COMPONENT_TYPE::TYPE_SPRITE)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	active = false;
	
}

sprite::~sprite()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void sprite:: serialize(FILE **filepp)
{
	char spriteName[256];
	memset(spriteName, 0, 256 * sizeof(char));

	fscanf_s(*filepp, "%255s\n", spriteName, sizeof(spriteName));

	
	pSurface = p_rm->load_surface(spriteName);
}

void sprite::draw_mesh()
{
	this->load_mesh();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void sprite::load_mesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Colour
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void sprite::serialize_graphic(char* path)
{
	FILE* fp;
	int rows, columns;
	char buffer[256];
	static float **map_data;

	fp = fopen(path, "r");

	if (!fp)
	{
		printf("Cannot open the file");
		return;

	}

	//getting rows and columns
	for (int i = 0; i<4; i++)
	{
		fscanf(fp, "%s", buffer);

		if (i == 1) 
		{
			columns = atoi(buffer);
		}
		if (i == 3) 
		{
			rows = atoi(buffer);
		}
	}
	for (int rws = 0; rws < rows; rws++)
	{
		for (int cols = 0; cols < columns; cols++)
		{
			fscanf(fp, "%s", buffer);
			vertices[rws * columns + cols] = atof(buffer);
		}
	}
}

void sprite::update()
{

}

void sprite::handle_event(Event* e)
{

}