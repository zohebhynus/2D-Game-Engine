/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include "resource_manager.h"
#include "SDL_surface.h"
#include "stdio.h"


resource_manager::resource_manager()
{

}

resource_manager::~resource_manager()
{
	for (auto &it : m_surface)
	{
		SDL_FreeSurface(it.second);
	}
}

SDL_Surface *resource_manager::load_surface(char *pPath)
{
	SDL_Surface *p_surface = m_surface[pPath];

	if (p_surface)
	{
		return p_surface;
	}

	p_surface = SDL_LoadBMP(pPath);

	if (p_surface)
	{
		m_surface[pPath] = p_surface;
	}

	return p_surface;
}