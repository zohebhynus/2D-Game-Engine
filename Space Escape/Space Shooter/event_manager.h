/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H
#include "SDL_stdinc.h"
#include "game_object_manager.h"
#include<unordered_map>
#include <list>

enum EVENT_TYPE
{
	COLLIDE,
	PLAYER_COLLISION,
	NUM
};

class Event
{
	public:
		Event(EVENT_TYPE type);
		virtual ~Event() {}

		EVENT_TYPE m_type;

		float m_timer;


};

class game_object;

class event_manager
{
public:
	event_manager();
	~event_manager();

	void broadcast_event(Event *p_event);
	void broadcast_event_to_subscribers(Event *p_event);
	void add_timed_event(Event *p_event);
	void update(float frame_time);
	void subscribe(EVENT_TYPE e_type, game_object *p_game_obj);

	std::list<Event*> m_events;
	std::unordered_map <EVENT_TYPE, std::list<game_object *>> m_subscriptions;

};
#endif