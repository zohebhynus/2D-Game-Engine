/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef SPRITE
#define SPRITE
#include "component.h"
#include <glew.h>
#include <gl\GL.h>
#include <iostream>
#include <stdio.h>

enum SHAPE_TYPE
{
	SPACESHIP,
	BULLET,
	ENEMYBASE1,
	ENEMYBASE2,
	ENEMYBASE3,
	ENEMYUD1,
	ENEMYUD2,
	NUM1
};

class game_object;
class SDL_Surface;

class sprite : public component
{
public:
	sprite();
	~sprite();

	void update();

	void serialize(FILE **filepp);
	void serialize_graphic(char* path);

	void draw_mesh();
	void load_mesh();

	void handle_event(Event* e);

	SDL_Surface *pSurface;

	GLuint VAO, VBO, EBO;
	GLfloat vertices[500];

	unsigned int m_type;
	bool active;
	
private:

};

#endif // 

