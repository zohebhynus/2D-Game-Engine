/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "body.h"
#include "transform.h"
#include "game_object.h"



body::body() : component(COMPONENT_TYPE::TYPE_BODY)
{
	m_pos_x = 0.0f;
	m_pos_y = 0.0f;
	
	m_prev_pos_x = 0.0f;
	m_prev_pos_y = 0.0f;
	
	m_vel_x = 0.0f;
	m_vel_y = 0.0f;
	
	m_acc_x = 0.0f;
	m_acc_y = 0.0f;

	m_total_force_x = 0.0f;
	m_total_force_y = 0.0f;
	
	m_mass = 0.0f;
	m_inv_mass = 0.0f;

	m_p_shape = NULL;
}
body::~body()
{
	if (m_p_shape)
	{
		delete m_p_shape;
	}
}


void body::serialize(FILE **fpp)
{
	//body mass
	fscanf_s(*fpp, "%f\n", &m_mass);

	if (m_mass)
		m_inv_mass = 1.0f / m_mass;
	else
		m_inv_mass = 0.0f;

	char shape_type[256];
	memset(shape_type, 0, sizeof(shape_type));

	//shape
	fscanf_s(*fpp, "%255s", shape_type, sizeof(shape_type));
	if (0 == strcmp(shape_type, "Circle"))
	{
		m_p_shape = new shape_circle();
		m_p_shape->p_owner_body = this;
		shape_circle *p_circle = static_cast<shape_circle *>(m_p_shape);
		fscanf_s(*fpp, "%f\n", &p_circle->m_radius);
	}
	else
	if (0 == strcmp(shape_type, "AABB"))
	{
		m_p_shape = new shape_AABB();
		m_p_shape->p_owner_body = this;
		shape_AABB *p_AABB = static_cast<shape_AABB *>(m_p_shape);
		fscanf_s(*fpp, "%f %f %f %f\n", &p_AABB->m_top, &p_AABB->m_bottom, &p_AABB->m_left, &p_AABB->m_right);
	}
}

void body::integrate(float gravity, float delta_time)
{
	
		//transform *pTr = static_cast<transform*>(p_owner->get_component(COMPONENT_TYPE::TYPE_TRANSFORM));
		transform *pTr = (transform*)p_owner->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);
		
		if (NULL != pTr)
		{
			m_pos_x = pTr->m_pos_x;
			m_pos_y = pTr->m_pos_y;
		}
	


	//prev position
	m_prev_pos_x = m_pos_x;
	m_prev_pos_y = m_pos_y;

	//accelration
	//m_total_force_y += gravity;
	m_acc_x = m_total_force_x * m_inv_mass;
	m_acc_y = m_total_force_y * m_inv_mass;

	//velocity
	m_vel_x = m_acc_x * delta_time + m_vel_x;
	m_vel_y = m_acc_y * delta_time + m_vel_y;

	//position
	m_pos_x = m_vel_x * delta_time + m_pos_x;

	m_pos_y = m_vel_y * delta_time + m_pos_y;

	//clearing force
	m_total_force_x = m_total_force_y = 0.0f;

	if (p_owner)
	{
		transform *p_tr = (transform*)p_owner->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);
		if (p_tr)
		{
			p_tr->m_pos_x = m_pos_x;
			p_tr->m_pos_y = m_pos_y;
		}
	}

}

void body::handle_event(Event* e)
{

}



