/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "transform.h"
#include "stdio.h"
 

transform::transform() : component(COMPONENT_TYPE :: TYPE_TRANSFORM)
{
	m_pos_x = 0.0f;
	m_pos_y = 0.0f;

	m_scale_x = 1.0f;
	m_scale_y = 1.0f;

	m_angle = 0.0f;
}

transform::~transform()
{

}

void transform::serialize(FILE ** filepp)
{
	fscanf_s(*filepp, "%f %f %f\n", &m_scale_x, &m_scale_y, &m_angle);
}



void transform:: update()
{
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(m_pos_x, m_pos_y, 0.0f));

	glm::mat4 scale;
	scale = glm::scale(scale, glm::vec3(m_scale_x, m_scale_y, 0.0f));

	glm::mat4 rotate;
	rotate = glm::rotate(rotate, glm::radians(m_angle), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 in;
	in = scale * rotate;

	m_p_transform = trans * in;
}

void transform::handle_event(Event* e)
{

}

