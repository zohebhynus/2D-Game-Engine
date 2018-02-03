/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "event_manager.h"

#include "game_object.h"
#include "frame_rate_controller.h"
#include <algorithm>

extern game_object_manager* p_gom;

Event::Event(EVENT_TYPE type)
{
	m_type = type;
	m_timer = 0.0f;
}

event_manager::event_manager()
{

}

event_manager::~event_manager()
{
	for (auto e : m_events)
	{
		delete e;
	}

	m_events.clear();
}

void event_manager::broadcast_event(Event *p_event)
{
	for (auto pGO : p_gom->m_game_objects)
	{
		pGO->handle_event(p_event);
	}
}

void event_manager::broadcast_event_to_subscribers(Event * p_event)
{
	std::list<game_object *> &list_subscribers = m_subscriptions[p_event->m_type];

	for (auto pGObj : list_subscribers)
	{
		pGObj->handle_event(p_event);
	}

}

void event_manager::add_timed_event(Event *p_event)
{
	m_events.push_back(p_event);

}

void event_manager::update(float frame_time)
{
	std::list<Event *>::iterator it_begin, it_end, it_temp;

	it_begin = m_events.begin();
	it_end = m_events.end();

	while (it_begin != it_end)
	{
		Event *p_event = *it_begin;
		p_event->m_timer -= frame_time;
		if (p_event->m_timer <= 0.0f)
		{
			
			broadcast_event_to_subscribers(p_event);

			delete p_event;
			it_temp = it_begin;
			++it_temp;
			m_events.erase(it_begin);
			it_begin = it_temp;
		}
		else
			++it_begin;
	}
}

void event_manager::subscribe(EVENT_TYPE e_type, game_object * p_game_obj)
{
	std::list<game_object *> &list_subscribers = m_subscriptions[e_type];
	{
		list_subscribers.push_back(p_game_obj);
	}

}