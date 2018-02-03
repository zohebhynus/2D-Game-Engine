/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef FRAME_RATE_CONTROLLER_H
#define FRAME_RATE_CONTROLLER_H


class frame_rate_controller
{
	public:
		frame_rate_controller(unsigned int max_FR);
		~frame_rate_controller();

		void frame_start();
		void frame_end();
		unsigned int get_frame_time();

private:
	unsigned int m_max_FR;
	unsigned int m_ticks_per_frame;

	unsigned int m_tick_start;
	unsigned int m_tick_end;

	unsigned int m_frame_time;
};

#endif	