/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef TRANSFORM
#define TRANSFORM
#include "component.h"
#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class game_object;

class transform : public component
{
public:
	transform();
	~transform();

	void update();
	void serialize(FILE **filepp);
	void handle_event(Event* e);

	float m_pos_x;
	float m_pos_y;

	float m_scale_x;
	float m_scale_y;
	float m_angle;

	glm::mat4 m_p_transform;

	

};

#endif // 

