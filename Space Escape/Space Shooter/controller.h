/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "component.h"
#include "event_manager.h"
#include "input_manager.h"
#include<stdio.h>



class player_collision_event : public Event
{
public:
	player_collision_event();
	~player_collision_event() {}
};

class controller : public component
{
public:
	controller();
	~controller();

	void update();
	void serialize(FILE **filepp);
	
	void handle_event(Event *e);

	int counter;
	int bullet_message=0;
	bool counter_check=true;
	
private:
};

#endif // 

