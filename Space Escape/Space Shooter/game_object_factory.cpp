/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "game_object_factory.h"
#include "stdio.h"
#include "game_object.h"
#include "sprite.h"
#include "transform.h"
#include "controller.h"
#include "resource_manager.h"	
#include "game_object_manager.h"
#include "body.h"
#include "collision_manager.h"
#include "up_down.h"

extern game_object_manager *p_gom;


game_object_factory::game_object_factory()
{
}

game_object_factory::~game_object_factory()
{

}

void game_object_factory::serialize(FILE ** filepp)
{
	
}

//Not Used
void game_object_factory::load_level(const char *pFileName)
{
	game_object* p_go = new game_object();

	FILE* lvl;
	lvl = fopen(pFileName, "r");

	char string_name[256];
	memset(string_name, 0, 256 * sizeof(char));

	while (fscanf(lvl, "%s", string_name) != EOF)
	{
		if (0 == strcmp("Player", string_name))
		{

			fscanf(lvl, "%s", string_name);

			p_go = create_object(string_name);
			transform* p_tr = new transform();
			p_go->add_component(p_tr);
			p_tr = (transform *)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);

			sprite* p_sp = new sprite();
			p_go->add_component(p_sp);
			p_sp = (sprite *)p_go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			p_sp->m_type = SPACESHIP;

			fscanf(lvl, "%f %f\n", &p_tr->m_pos_x, &p_tr->m_pos_y);
			

		}
		if (0 == strcmp("Bullet", string_name))
		{
			fscanf(lvl, "%s", string_name);

			p_go = create_object(string_name);
			transform* p_tr = new transform();
			p_go->add_component(p_tr);
			p_tr = (transform *)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);

			sprite* p_sp = new sprite();
			p_go->add_component(p_sp);
			p_sp = (sprite *)p_go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			p_sp->m_type = BULLET;

			fscanf(lvl, "%f %f\n", &p_tr->m_pos_x, &p_tr->m_pos_y);
			

		}
		if (0 == strcmp("EnemyBase1", string_name))
		{
			fscanf(lvl, "%s", string_name);

			p_go = create_object(string_name);
			transform* p_tr = new transform();
			p_go->add_component(p_tr);
			p_tr = (transform *)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


			sprite* p_sp = new sprite();
			p_go->add_component(p_sp);
			p_sp = (sprite *)p_go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			p_sp->m_type = ENEMYBASE1;

			fscanf(lvl, "%f %f\n", &p_tr->m_pos_x, &p_tr->m_pos_y);
			

		}
		if (0 == strcmp("EnemyBase2", string_name))
		{
			fscanf(lvl, "%s", string_name);

			p_go = create_object(string_name);
			transform* p_tr = new transform();
			p_go->add_component(p_tr);
			p_tr = (transform *)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


			sprite* p_sp = new sprite();
			p_go->add_component(p_sp);
			p_sp = (sprite *)p_go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			p_sp->m_type = ENEMYBASE2;

			fscanf(lvl, "%f %f\n", &p_tr->m_pos_x, &p_tr->m_pos_y);
			

		}
		if (0 == strcmp("EnemyBase3", string_name))
		{
			fscanf(lvl, "%s", string_name);

			p_go = create_object(string_name);
			transform* p_tr = new transform();
			p_go->add_component(p_tr);
			p_tr = (transform *)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


			sprite* p_sp = new sprite();
			p_go->add_component(p_sp);
			p_sp = (sprite *)p_go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			p_sp->m_type = ENEMYBASE3;

			fscanf(lvl, "%f %f\n", &p_tr->m_pos_x, &p_tr->m_pos_y);
			

		}
		if (0 == strcmp("EnemyUD1", string_name))
		{
			fscanf(lvl, "%s", string_name);

			p_go = create_object(string_name);
			transform* p_tr = new transform();
			p_go->add_component(p_tr);
			p_tr = (transform *)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


			sprite* p_sp = new sprite();
			p_go->add_component(p_sp);
			p_sp = (sprite *)p_go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			p_sp->m_type = ENEMYUD1;

			fscanf(lvl, "%f %f\n", &p_tr->m_pos_x, &p_tr->m_pos_y);
			

		}
		if (0 == strcmp("EnemyUD2", string_name))
		{
			fscanf(lvl, "%s", string_name);

			p_go = create_object(string_name);
			transform* p_tr = new transform();
			p_go->add_component(p_tr);
			p_tr = (transform *)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


			sprite* p_sp = new sprite();
			p_go->add_component(p_sp);
			p_sp = (sprite *)p_go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			p_sp->m_type = ENEMYUD2;

			fscanf(lvl, "%f %f\n", &p_tr->m_pos_x, &p_tr->m_pos_y);
			

		}

	}
}

game_object  *game_object_factory::create_object(const char * pFileName)
{
	char string_name[256];
	memset(string_name, 0, 256 * sizeof(char));
	game_object *p_new_object = new game_object;

	FILE *fp;
	fp = fopen(pFileName, "r");

	
	if (fp)
	{
		while (fscanf(fp, "%s\n", string_name) != EOF)
		{	
			if (strcmp(string_name, "Transform") == 0)
			{
				transform *p_tr = new transform();
				p_new_object->add_component(p_tr);
				p_tr = (transform *)p_new_object->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);
				p_tr->p_owner = p_new_object;
				p_tr->serialize(&fp);
			}

			else
			if (strcmp(string_name, "Sprite") == 0)
			{
				char vertices_file[256];
				sprite *p_sp = new sprite();
				p_new_object->add_component(p_sp);
				p_sp = (sprite *)p_new_object->get_component(COMPONENT_TYPE::TYPE_SPRITE);
				p_sp->p_owner = p_new_object;

				fscanf(fp, "%s", vertices_file);
				printf("Loading %s \n", vertices_file);
				p_sp->serialize_graphic(vertices_file);
			}

			else
			if (strcmp(string_name, "Controller") == 0)
			{
				controller *pCtrl = new controller();
				p_new_object->add_component(pCtrl);
				pCtrl = (controller *)p_new_object->get_component(COMPONENT_TYPE::TYPE_CONTROLLER);
				pCtrl->p_owner = p_new_object;
				pCtrl->serialize(&fp);
			}
			else
			if (strcmp(string_name, "Body") == 0)
			{
				body *pBody = new body();
				p_new_object->add_component(pBody);
				pBody = (body *)p_new_object->get_component(COMPONENT_TYPE::TYPE_BODY);
				pBody->p_owner = p_new_object;
				pBody->serialize(&fp);
			}
			else
			if (strcmp(string_name, "UpDown") == 0)
			{
				up_down *pUD = new up_down();
				p_new_object->add_component(pUD);
				pUD = (up_down *)p_new_object->get_component(COMPONENT_TYPE::TYPE_UPDOWN);
				pUD->p_owner = p_new_object;
				pUD->serialize(&fp);
			}
		}
		
		p_gom->m_game_objects.push_back(p_new_object);
		fclose(fp);
	}
	return p_new_object;
}



void game_object_factory:: update()
{

}

