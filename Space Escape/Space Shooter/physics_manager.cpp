/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "physics_manager.h"
#include "game_object_manager.h"
#include "game_object.h"
#include "body.h"
#include "collision_manager.h"
#include "frame_rate_controller.h"
#include "transform.h"


extern game_object_manager *p_gom;
extern frame_rate_controller *p_frc;
//extern collision_manager *p_CM;

collide_event::collide_event() : Event(EVENT_TYPE::COLLIDE)
{
	m_p_object1 = m_p_object2 = NULL;
}


physics_manager::physics_manager(float gravity)
{
	m_gravity = gravity;
	p_CM = new collision_manager();
}

physics_manager::~physics_manager()
{
	
}

void physics_manager::update(float FrameTime)
{
	//integrate
	for (game_object *go : p_gom->m_game_objects)
	{
		body *pBody = (body *)go->get_component(COMPONENT_TYPE::TYPE_BODY);
		if (NULL == pBody)
			continue;

		pBody->integrate(m_gravity, FrameTime);
	}

	//reset contacts
	p_CM->reset();

	//Generate contacts
	if (p_gom->m_game_objects.size())
	{
		auto p_obj1 = p_gom->m_game_objects.begin();
		auto p_obj_last = p_gom->m_game_objects.end();
		--p_obj_last;

		for (; p_obj1 != p_obj_last; ++p_obj1)
		{
			body *pBody1 = (body*)(*p_obj1)->get_component(COMPONENT_TYPE::TYPE_BODY);
			sprite* pSp1 = (sprite *)(*p_obj1)->get_component(COMPONENT_TYPE::TYPE_SPRITE);

			if (pBody1 == NULL)
				continue;

			auto p_obj2 = p_obj1 + 1;
			for (; p_obj2 != p_gom->m_game_objects.end(); ++p_obj2)
			{
				body *pBody2 = (body *)(*p_obj2)->get_component(COMPONENT_TYPE::TYPE_BODY);
				sprite* pSp2 = (sprite *)(*p_obj2)->get_component(COMPONENT_TYPE::TYPE_SPRITE);
				if (NULL == pBody2)
					continue;

				if ((pSp1->m_type == BULLET && pSp2->m_type == SPACESHIP) || (pSp2->m_type == BULLET && pSp1->m_type == SPACESHIP))
					continue;

				p_CM->check_collision_generate_contact(pBody1->m_p_shape, pBody1->m_pos_x, pBody1->m_pos_y, pBody2->m_p_shape, pBody2->m_pos_x, pBody2->m_pos_y);
			}
		}

		for (auto cont : p_CM->m_contacts)
		{
			collide_event collide_event;

			collide_event.m_p_object1 = cont->bodies[0]->p_owner;
			collide_event.m_p_object2 = cont->bodies[1]->p_owner;

			cont->bodies[0]->p_owner->handle_event(&collide_event);
			cont->bodies[1]->p_owner->handle_event(&collide_event);

		}


		//commit changes to trnasform component
		for (game_object *pGObj : p_gom->m_game_objects)
		{
			sprite* pSP = (sprite*)pGObj->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			body *pBo = (body *)pGObj->get_component(COMPONENT_TYPE::TYPE_BODY);
			transform *p_trans = (transform *)pGObj->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);

			if (pBo && p_trans)
			{
				p_trans->m_pos_x = pBo->m_pos_x;
				p_trans->m_pos_y = pBo->m_pos_y;
			}

		}
	}

}

	