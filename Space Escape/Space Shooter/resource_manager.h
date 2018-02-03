/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/


#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include "SDL_stdinc.h"
#include <unordered_map>
#include <string>


class SDL_Surface;

class resource_manager
{
	public:
		resource_manager();
		~resource_manager();

		SDL_Surface *load_surface(char *pPath);

private:

	std::unordered_map<std::string, SDL_Surface*>m_surface;
	
};

#endif	