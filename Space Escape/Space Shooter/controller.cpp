/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "controller.h"
#include "input_manager.h"
#include "SDL_keyboard.h"
#include "game_object.h"
#include "transform.h"
#include "body.h"
#include "physics_manager.h"
#include "frame_rate_controller.h"
#include "game_object_manager.h"



extern event_manager *p_em;
extern input_manager *p_im;
extern frame_rate_controller *p_frc;
extern game_object_manager* p_gom;
extern controller* timer;

player_collision_event::player_collision_event() : Event(EVENT_TYPE::PLAYER_COLLISION)
{

}

controller::controller() : component(COMPONENT_TYPE::TYPE_CONTROLLER)
{
	
}

controller::~controller()
{

}

void controller:: update()
{
	float forward_acc = 1.0f;
	float backward_acc = -1.0f;
	
	p_im->update();

	transform *p_trans = static_cast<transform *>(p_owner->get_component(COMPONENT_TYPE::TYPE_TRANSFORM));
	body *pBody = static_cast<body*>(p_owner->get_component(COMPONENT_TYPE::TYPE_BODY));
		if (pBody == NULL)
	{
		return;
	}

	if (p_im->key_pressed(SDL_SCANCODE_UP))
	{
		pBody->m_total_force_x = forward_acc * cosf((p_trans->m_angle + 90) *3.14 / 180);
		pBody->m_total_force_y = forward_acc * sinf((p_trans->m_angle + 90) *3.14 / 180);
	}
		 
	if (p_im->key_pressed(SDL_SCANCODE_DOWN))
	{
		pBody->m_total_force_x = backward_acc * cosf((p_trans->m_angle + 90) *3.14 / 180);
		pBody->m_total_force_y = backward_acc * sinf((p_trans->m_angle + 90) *3.14 / 180);
	}

	if (p_im->key_pressed(SDL_SCANCODE_LEFT))
	{
		p_trans->m_angle += 0.2f * p_frc->get_frame_time();
	}

	if (p_im->key_pressed(SDL_SCANCODE_RIGHT))
	{
		p_trans->m_angle -= 0.2f * p_frc->get_frame_time();
	}

	if (p_im->key_pressed(SDL_SCANCODE_SPACE))
	{
		//Get the bullet object
		
			for (game_object* p_obj : p_gom->m_game_objects)
			{
				game_object* bullet = new game_object;

				sprite* p_sp = (sprite*)p_obj->get_component(COMPONENT_TYPE::TYPE_SPRITE);

				for (auto i : p_obj->m_component)
				{
					if (p_sp->m_type == BULLET)
					{
						transform* bullet_p_tr = (transform*)p_obj->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);

						if (bullet_p_tr->m_pos_x > 1.1f || bullet_p_tr->m_pos_x < -1.1f || bullet_p_tr->m_pos_y>1.1f || bullet_p_tr->m_pos_y < -1.1f)
						{

							++bullet_message;
							if (bullet_message == 1)
								printf("\n\nLOL. These tiny bullets dont work against these asteriods. You'll have to survive without them %d.\n\n",bullet_message);

							if (bullet_message == 2)
								printf("I already told you, you can't shoot them. So just stop! %d\n\n",bullet_message);

							if (bullet_message == 3)
								printf("Can you please not do that? You are ruining the timer. %d\n\n",bullet_message);

							if (bullet_message == 4)
								printf("Alright! I am deactivating this.%d\n\n",bullet_message);


							if (bullet_message == 1 || bullet_message == 2 || bullet_message == 3 || bullet_message == 4)
							{

								bullet_p_tr->m_pos_x = p_trans->m_pos_x;
								bullet_p_tr->m_pos_y = p_trans->m_pos_y;

								bullet_p_tr->m_angle = p_trans->m_angle;

								body* bullet_body = (body *)p_obj->get_component(COMPONENT_TYPE::TYPE_BODY);

								game_object* ship = p_trans->p_owner;

								body* ship_body = (body *)ship->get_component(COMPONENT_TYPE::TYPE_BODY);

								bullet_body->m_vel_x = 0;
								bullet_body->m_vel_y = 0;
							

							if (NULL != bullet_body)
							{
								bullet_body->m_total_force_x = ship_body->m_acc_x + (100.0f * cosf((p_trans->m_angle + 90) *3.14 / 180));
								bullet_body->m_total_force_y = ship_body->m_acc_y + (100.0f * sinf((p_trans->m_angle + 90) *3.14 / 180));
							}
							//printf("Ship Angle: %f\n", p_trans->m_angle);
						}
						}

					}
				}
			}
		
	}
}

void controller:: serialize(FILE **filepp)
{
	
}

void controller::handle_event(Event *p_event)
{
	if (EVENT_TYPE::COLLIDE == p_event->m_type)
	{
		collide_event *p_real_event = (collide_event *)p_event;

		body *pBody = (body *)p_owner->get_component(COMPONENT_TYPE::TYPE_BODY);

		if (pBody)
		{
			
			pBody->m_pos_x = 0.0f;
			pBody->m_pos_y = 0.0f;
			pBody->m_vel_x = 0.0f;
			pBody->m_vel_y = 0.0f;
		}
		
		for (game_object *go : p_gom->m_game_objects)
		{
			sprite* del = (sprite*)go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			if (del->m_type == ENEMYUD1)
			{
				body* del_b = (body*)go->get_component(COMPONENT_TYPE::TYPE_BODY);
				del_b->m_pos_x = 100;
				del_b->m_pos_y = 100;
			}
			if (del->m_type == ENEMYUD2)
			{
				body* del_b = (body*)go->get_component(COMPONENT_TYPE::TYPE_BODY);
				del_b->m_pos_x = 100;
				del_b->m_pos_y = 100;
			}
			if (del->m_type == ENEMYBASE1)
			{
				body* del_b = (body*)go->get_component(COMPONENT_TYPE::TYPE_BODY);
				del_b->m_pos_x = 100;
				del_b->m_pos_y = 100;
			}
			if (del->m_type == ENEMYBASE2)
			{
				body* del_b = (body*)go->get_component(COMPONENT_TYPE::TYPE_BODY);
				del_b->m_pos_x = 100;
				del_b->m_pos_y = 100;
			}
			if (del->m_type == ENEMYBASE3)
			{
				body* del_b = (body*)go->get_component(COMPONENT_TYPE::TYPE_BODY);
				del_b->m_pos_x = 100;
				del_b->m_pos_y = 100;
			}
			if (del->m_type == SPACESHIP)
			{
				body* del_b = (body*)go->get_component(COMPONENT_TYPE::TYPE_BODY);
				del_b->m_pos_x = 400;
				del_b->m_pos_y =400;
			}

			/*	player_collision_event *p_PCE = new player_collision_event();
				p_PCE->m_timer = 1.0f;
				p_em->add_timed_event(p_PCE);*/
		}
		if (timer->counter > 10)
		{
			printf("\n------------YOU WIN------------\n");
			printf("You survived for %d seconds.\n", timer->counter);
		}
		else if (timer->counter < 10)
		{
			printf("\n------------YOU LOSE------------\n");
			printf("You survived for %d seconds.\n", timer->counter);
			printf("Meh.. You could've done better.\n");
		}
		timer->counter_check = false;
	}
}