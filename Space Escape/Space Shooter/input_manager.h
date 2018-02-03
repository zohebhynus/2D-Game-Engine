/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H
#include "SDL_stdinc.h"

class input_manager
{
	public:
		input_manager();
		~input_manager();

		void update();

		bool key_pressed(unsigned int KeyScanCode);
		bool key_triggered(unsigned int KeyScanCode);
		bool key_released(unsigned int KeyScanCode);

	private:
		Uint8 mPreviousState[512];
		Uint8 mCurrentState[512];
};
#endif