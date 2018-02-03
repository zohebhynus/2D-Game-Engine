/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef COMPONENT
#define COMPONENT
#include <stdio.h>
#include "event_manager.h"

class game_object;
class Event;

struct COMPONENT_TYPE
{
	enum
	{
		TYPE_TRANSFORM,
		TYPE_SPRITE,
		TYPE_CONTROLLER,
		TYPE_BODY,
		TYPE_UPDOWN
	};
};

class component
{
public:
	component() {}
	component(unsigned int type);
	virtual ~component() {}

	virtual void update() = 0;

	virtual void serialize(FILE **filepp)=0;
	virtual void handle_event(Event* e) {};

	game_object* p_owner;
	unsigned int m_type;
};

#endif // 

