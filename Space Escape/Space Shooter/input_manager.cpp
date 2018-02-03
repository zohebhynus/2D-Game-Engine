/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "input_manager.h"
#include "SDL_config.h"
#include "memory.h"
#include "SDL_keyboard.h"
input_manager::input_manager()
{
	memset(mCurrentState,0,512*sizeof(Uint8));
	

}

input_manager::~input_manager()
{

}

void input_manager::update()
{
	int fetchedNum = 0;
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(&fetchedNum);
	
	if (fetchedNum > 512)fetchedNum = 512;

	memcpy(mPreviousState, mCurrentState, 512 * sizeof(Uint8));

	memcpy(mCurrentState,currentKeyStates,fetchedNum*sizeof(Uint8));
} 

bool input_manager::key_pressed(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode])
		return true;

	return false;
}

bool input_manager::key_triggered(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode] && !mPreviousState[KeyScanCode])
	{
		return true;
	}

	
	return false;
}

bool input_manager::key_released(unsigned int KeyScanCode)
{
	if (KeyScanCode >= 512)
	{
		return false;
	}

	if (!mCurrentState[KeyScanCode] && mPreviousState[KeyScanCode])
	{
		return true;
	}

	return false;
}
