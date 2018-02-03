/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "up_down.h"
#include "stdio.h"
#include "transform.h"
#include "game_object.h"
#include "event_manager.h"
#include "controller.h"
#include "frame_rate_controller.h"

extern frame_rate_controller *p_frc;
extern event_manager *p_em;

up_down::up_down() : component(COMPONENT_TYPE :: TYPE_UPDOWN)
{
	

	m_pos_x = 0;
	m_pos_y = 0;
	up = false;


}

up_down::~up_down()
{

}

void up_down::serialize(FILE ** filepp)
{
	
	fscanf_s(*filepp, "%d \n", &m_pos_x);
	
	
	{
		p_em->subscribe(EVENT_TYPE::PLAYER_COLLISION, this->p_owner);
	}
}



void up_down:: update()
{
	transform *pTrans = static_cast<transform *>(p_owner->get_component(COMPONENT_TYPE::TYPE_TRANSFORM));

	if (pTrans == NULL)
	{
		return;
	}

	if (!up)
	{
		if (pTrans->m_pos_x < m_pos_x) 
		{

			pTrans->m_pos_x= pTrans->m_pos_x + 0.009;
		}
		else 
		{
			up = true;
		}
	}

	if (up)
	{
		if (pTrans->m_pos_x > -m_pos_x) 
		{

			pTrans->m_pos_x=pTrans->m_pos_x - 0.009;
		}
		else {

			up = false;
		}
	}
}

void up_down::handle_event(Event *p_event)
{
	if (EVENT_TYPE::PLAYER_COLLISION == p_event->m_type)
	{
		player_collision_event *p_real_event = (player_collision_event *)p_event;

		transform *pTrans = (transform *)p_owner->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);
		if (pTrans)
			pTrans->m_pos_y -= 0.2f;
	}
}

