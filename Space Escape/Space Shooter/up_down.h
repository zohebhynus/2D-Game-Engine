/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef UP_DOWN
#define UP_DOWN
#include "component.h"

class game_object;

class up_down : public component
{
public:
	up_down();
	~up_down();

	void update();
	void serialize(FILE **filepp);
	void handle_event(Event *pEvent);

	int m_pos_x;
	int m_pos_y;
	bool up;
	game_object *p_owner;

};

#endif // 

