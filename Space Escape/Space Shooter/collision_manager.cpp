/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "collision_manager.h"
#include "game_object_manager.h"
#include "game_object.h"
#include "body.h"
#include <iostream>

extern game_object_manager *p_gom;

shape::shape(SHAPE_TYPE type)
{
	m_shape_type = type;
	p_owner_body = NULL;
}

bool check_collision_circle_circle(shape *p_circle1, float pos1_x, float pos1_y, shape *p_circle2, float pos2_x, float pos2_y, std::vector<contact*>&m_contacts)
{
	float cc_sq_dist, r1, r2;

	cc_sq_dist = (pos2_x - pos1_x)*(pos2_x - pos1_x) + (pos2_y - pos1_y)*(pos2_y - pos1_y);
	r1 = ((shape_circle*)p_circle1)->m_radius;
	r2 = ((shape_circle*)p_circle2)->m_radius;

	if (cc_sq_dist > (r1 + r2)*(r1 + r2))
	{
		return false;
	}

	/*contact *p_new_contact = new contact;
	p_new_contact->bodies[0] = p_circle1->p_owner_body;
	p_new_contact->bodies[1] = p_circle2->p_owner_body;

	m_contacts.push_back(p_new_contact);*/

	return true;
}

bool check_collision_AABB_AABB(shape *p_AABB1, float pos1_x, float pos1_y, shape *p_AABB2, float pos2_x, float pos2_y, std::vector<contact*>&m_contacts)
{
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	shape_AABB *p_s_AABB1 = (shape_AABB *)p_AABB1;
	shape_AABB *p_s_AABB2 = (shape_AABB *)p_AABB2;

	left1 = pos1_x - p_s_AABB1->m_left;
	left2 = pos2_x - p_s_AABB2->m_left;

	right1 = pos1_x + p_s_AABB1->m_right;
	right2 = pos2_x + p_s_AABB2->m_right;

	top1 = pos1_y - p_s_AABB1->m_top;
	top2 = pos2_y - p_s_AABB2->m_top;

	bottom1 = pos1_y + p_s_AABB1->m_bottom;
	bottom2 = pos2_y + p_s_AABB2->m_bottom;

	return !(left2 > right1 || right2 < left1 || top2 > bottom1 || bottom2 < top1);


	/*contact *p_new_contact = new contact;
	p_new_contact->bodies[0] = p_AABB1->p_owner_body;
	p_new_contact->bodies[1] = p_AABB2->p_owner_body;

	m_contacts.push_back(p_new_contact);*/


}

bool check_collision_circle_AABB(shape *p_circle, float pos1_x, float pos1_y, shape *p_AABB, float pos2_x, float pos2_y, std::vector<contact*>&m_contacts)
{
	shape_circle *p_s_Circle = (shape_circle *)p_circle;
	shape_AABB *p_s_AABB = (shape_AABB *)p_AABB;
	float top, left, bottom, right;

	top = pos2_y - p_s_AABB->m_top;
	left = pos2_x - p_s_AABB->m_left;
	bottom = pos2_y + p_s_AABB->m_bottom;
	right = pos2_x + p_s_AABB->m_right;
	

	float new_x, new_y;

	if (pos1_x < left)
	{
		new_x = left;
	}
	else
	if (pos1_x > right)
	{
		new_x = right;
	}
	else
		new_x = pos2_x;


	if (pos1_y < top)
	{
		new_y = top;
	}
	else
	if (pos1_y > bottom)
	{
		new_y = bottom;
	}
	else
		new_y = pos2_y;

	if (p_circle->test_point(new_x, new_y) == false)
	{
		return false;
	}

	/*contact *p_new_contact = new contact;
	p_new_contact->bodies[0] = p_circle->p_owner_body;
	p_new_contact->bodies[1] = p_AABB->p_owner_body;
	m_contacts.push_back(p_new_contact);*/

	return true;

	return false;

}




collision_manager::~collision_manager()
{

}


bool shape_circle::test_point(float point_x, float point_y)
{
	float sq_dist = (point_x - p_owner_body->m_pos_x)*(point_x - p_owner_body->m_pos_x) + (point_y - p_owner_body->m_pos_y)*(point_y - p_owner_body->m_pos_y);

	if (sq_dist>m_radius*m_radius)
	{
		return false;
	}

	return true;
}

bool shape_AABB::test_point(float point_x, float point_y)
{
	float left, right, top, bottom;
	left = p_owner_body->m_pos_x - m_left;
	right = p_owner_body->m_pos_x - m_right;
	top = p_owner_body->m_pos_y - m_top;
	bottom = p_owner_body->m_pos_y - m_bottom;

	if (point_x<left || point_x > right || point_y<top || point_y>bottom)
	{
		return false;
	}

	return true;
}

collision_manager::collision_manager() :m_contacts()
{
	f_ptr[shape::SHAPE_TYPE::CIRCLE][shape::SHAPE_TYPE::CIRCLE] = check_collision_circle_circle;
	f_ptr[shape::SHAPE_TYPE::CIRCLE][shape::SHAPE_TYPE::AABB] = check_collision_circle_AABB;
	f_ptr[shape::SHAPE_TYPE::AABB][shape::SHAPE_TYPE::AABB] = check_collision_AABB_AABB;
	f_ptr[shape::SHAPE_TYPE::AABB][shape::SHAPE_TYPE::CIRCLE] = check_collision_circle_AABB;
}

bool collision_manager::check_collision_generate_contact(shape *p_shape1, float pos1_x, float pos1_y, shape *p_shape2, float pos2_x, float pos2_y)
{
	bool result= f_ptr[p_shape1->m_shape_type][p_shape2->m_shape_type](p_shape1, pos1_x, pos1_y, p_shape2, pos2_x, pos2_y, m_contacts);
	if (result)
	{
		contact* tm = new contact();
		tm->bodies[0] = p_shape1->p_owner_body;
		tm->bodies[1] = p_shape2->p_owner_body;
		m_contacts.push_back(tm);
	}
	return result;

}

void collision_manager::reset()
{
	for (auto con : m_contacts)
	{
		delete con;
	}
	m_contacts.clear();
}



	