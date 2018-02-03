/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H
#include<stdio.h>
#include "event_manager.h"

class  collision_manager;
class game_object;

class collide_event : public Event
{
public:
	collide_event();
	~collide_event() {};

	game_object *m_p_object1;
	game_object *m_p_object2;
};

class physics_manager
{
public:
	physics_manager(float gravity);
	~physics_manager();
	float m_gravity;

	void update(float dt);

	
public:

	collision_manager *p_CM;


private:
};

#endif // 

