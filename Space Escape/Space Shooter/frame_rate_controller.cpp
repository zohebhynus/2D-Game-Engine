/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "frame_rate_controller.h"
#include "stdio.h"
#include "limits.h"
#include "SDL_timer.h"

frame_rate_controller::frame_rate_controller(unsigned int max_FR)
{
	if (m_max_FR == 0)
	{
		m_max_FR = UINT_MAX;
	}

	m_max_FR = max_FR;
	m_ticks_per_frame = 1000 / m_max_FR;

	m_tick_start = 0;
	m_tick_end = 0;

	m_frame_time = 0;

}

frame_rate_controller::~frame_rate_controller()
{

}

void frame_rate_controller::frame_start()
{
	m_tick_start = SDL_GetTicks();
}

void frame_rate_controller::frame_end()
{
	m_tick_end = SDL_GetTicks();

	while (m_tick_end - m_tick_start < m_ticks_per_frame)
	{
		m_tick_end = SDL_GetTicks();
	}
	
	m_frame_time = m_tick_end - m_tick_start;
}

unsigned int frame_rate_controller::get_frame_time()
{
	return m_frame_time;
}