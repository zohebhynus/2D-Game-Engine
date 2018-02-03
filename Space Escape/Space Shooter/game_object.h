/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "event_manager.h"
#include <vector>
#include "transform.h"
#include "sprite.h"
#include "controller.h"
#include "body.h"
#include "up_down.h"


class component;

class game_object
{
public:
	game_object();
	~game_object();

	void update();
	void add_component(component *p_component);
	component *get_component(unsigned int Type);
	
	void handle_event(Event *p_event);
	
	
	std::vector<component*>  m_component;

	bool m_active;


};

#endif // 

