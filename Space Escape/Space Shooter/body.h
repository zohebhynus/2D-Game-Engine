/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef BODY_H
#define BODY_H
#include<stdio.h>
#include "component.h"
#include "event_manager.h"
#include "collision_manager.h"

class collision_manager;
class shape;
class game_object;


class body : public component
{
public:
	body();
	~body();

	void update(void) {}
	void serialize(FILE **fpp);
	void integrate(float delta_time, float gravity);
	void handle_event(Event* e);

	float m_pos_x;
	float m_pos_y;

	float m_prev_pos_x;
	float m_prev_pos_y;

	float m_vel_x;
	float m_vel_y;

	float m_acc_x;
	float m_acc_y;

	float m_total_force_x;
	float m_total_force_y;

	float m_mass;
	float m_inv_mass;

	shape *m_p_shape;
};

#endif // 

