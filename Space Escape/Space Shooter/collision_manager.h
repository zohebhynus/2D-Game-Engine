/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H


#include<list>
#include<vector>

class body;

class contact
{
public:
	contact()
	{
		bodies[0] = NULL;
		bodies[1] = NULL;
	}
	~contact() {}

	body *bodies[2];
};

class shape
{
public:
	enum SHAPE_TYPE
	{
		CIRCLE,
		AABB,

		NUM
	};
	shape(SHAPE_TYPE type);
	virtual ~shape() {}
	virtual bool test_point(float point_x, float point_y) = 0;

public:
	body *p_owner_body;
	SHAPE_TYPE m_shape_type;

private:

};


class shape_circle : public shape
{
public:
	shape_circle() : shape(shape::CIRCLE)
	{
		m_radius = 0.0f; 
	}
	~shape_circle() {}
	bool test_point(float point_x, float point_y);


	float m_radius;

private:

};

class shape_AABB : public shape
{
public:
	shape_AABB()  : shape(shape::AABB)
	{ 
		m_left = m_right = m_top = m_bottom = 0.0f; 
	}

	~shape_AABB() {}

	bool test_point(float point_x, float point_y);

	float m_left, m_right, m_top, m_bottom;

private:

};

class collision_manager
{
public:

	std::vector<contact*> m_contacts;
	bool(*f_ptr[shape::SHAPE_TYPE::NUM-1][shape::SHAPE_TYPE::NUM-1]) (shape* shape1, float pos1_x, float pos1_y, shape* shape2, float pos2_x, float pos2_y, std::vector<contact*>&m_contacts);
	
	
	collision_manager();
	~collision_manager();

	void reset();

	bool check_collision_generate_contact(shape *p_shape1, float pos1_x, float pos1_y, shape *p_shape2, float pos2_x, float pos2_y);
};



#endif // 

