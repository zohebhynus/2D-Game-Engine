/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "component.h"
#include <string>

class component;

class game_object_manager;

class game_object_factory : public component
{
public:
	game_object_factory();
	~game_object_factory();

	void update();
	void serialize(FILE **filepp);

	
	void load_level(const char *pFileName);

	game_object *create_object(const char *pFileName);
	


	

};
 

