/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "game_object.h"
#include "stdio.h"


game_object::game_object()
{
	m_active = false;
}

game_object::~game_object()
{
	for (auto comp : m_component)
	{
		delete comp;
	}
	m_component.clear();
}

void game_object:: update()
{
	for (auto comp : m_component)
	{
		comp->update();
	}

}

void game_object::add_component(component *p_component)
{
	p_component->p_owner = this;

	m_component.push_back(p_component);
}

component * game_object::get_component(unsigned int type)
{
	for (auto comp : m_component)
	{
		if (comp->m_type == type)
			return comp;
	}

	return NULL;
}


void game_object::handle_event(Event *p_event)
{
	for (auto comp : m_component)
	{
		comp->handle_event(p_event);
	}
}




