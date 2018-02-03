/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
Language: C++
Platform: Microsoft (R) C/C++ Optimizing Compiler Version 19.00.24213.1 for x86
Project: CS529_zoheb.hynus_final
Author: Zoheb Hynus, zoheb.hynus, 60000517
Creation date: 12/17/2017
- End Header --------------------------------------------------------*/

#include <SDL.h>
#include <glew.h>
#include <GLFW\glfw3.h>
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stdio.h"
#include "input_manager.h"
#include "resource_manager.h"
#include "frame_rate_controller.h"
#include "game_object.h"
#include "game_object_manager.h"
#include "sprite.h"
#include "transform.h"
#include "windows.h"
#include "controller.h"
#include "game_object_factory.h"
#include "body.h"
#include "physics_manager.h"
#include "event_manager.h"


int counter;
game_object_manager *p_gom;
input_manager *p_im;
resource_manager *p_rm;
frame_rate_controller *p_frc;
game_object_factory *p_gof;
physics_manager *p_pm;
event_manager *p_em;
controller* timer = new controller();
void wrap(game_object* p_go);

static game_object* spc_shp;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")



int main(int argc, char* args[])
{
	int index = 0;
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle("spaceConsole");
	}


	SDL_Window *pWindow;
	int error = 0;
	bool isAppRunning = true;
	p_im = new input_manager();
	p_frc = new frame_rate_controller(60);
	p_rm = new resource_manager();
	p_gom = new game_object_manager();
	p_gof = new game_object_factory();
	p_pm = new physics_manager(1.0f);
	p_em = new event_manager();
	SDL_Surface *pWindowSurface = NULL;





	/* Initialize SDL*/
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}
	SDL_GLContext mainContext;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


	pWindow = SDL_CreateWindow("Space Escape",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		600,										// height, in pixels
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	/*Check that the window was successfully made*/
	if (NULL == pWindow)
	{
		/* In the event that the window could not be made...*/
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	/* get window surface*/
	mainContext = SDL_GL_CreateContext(pWindow);
	glewExperimental = GL_TRUE;
	glewInit();

	/*update window surface*/
	//SDL_UpdateWindowSurface(pWindow);

	// creating game objects
	{
		p_gof->load_level("Level1.txt");
	}




	printf("\n-----------SPACE ESCAPE--------------\n");
	printf("Survive for at least 10 seconds to win\n");
	// Game loop
	while (true == isAppRunning)
	{
		p_frc->frame_start();
		if (timer->counter_check == true)
		{
			++counter;
			if (counter % 60 == 0)
			{
				int p = counter / 60;
				printf("seconds:%d\n", p);

				timer->counter = p;
			}
		}
		
		Shader shader("vertex.vs", "fragment.frag");
		shader.Use();

		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				isAppRunning = false;
			}
		}

		//printf("Frame Time: %u \n", p_frc->get_frame_time());

		//SDL_FillRect(pWindowSurface, NULL, 0);



		p_pm->update(p_frc->get_frame_time() / 1000.0f);
		p_im->update();
		p_em->update(p_frc->get_frame_time() / 1000.0f);


		//updating game objects
		for (game_object *go : p_gom->m_game_objects)
		{
			go->update();
		}



		for (game_object *go : p_gom->m_game_objects)
		{
			sprite *pSprite = (sprite *)go->get_component(COMPONENT_TYPE::TYPE_SPRITE);
			controller* pController = (controller*)go->get_component(COMPONENT_TYPE::TYPE_CONTROLLER);

			for (auto a : go->m_component)
			{
				a->update();
			}

			if (pController)
			{
				spc_shp = go;
				
			}
		}

		//Clearing the buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Send to shaders and draw Draw Loop
		for (game_object* p_ob : p_gom->m_game_objects)
		{

			//Get the transformation matrice
			transform* p_tr = (transform*)p_ob->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);
			sprite* p_sp = (sprite*)p_ob->get_component(COMPONENT_TYPE::TYPE_SPRITE);

			if (NULL == p_tr || NULL == p_sp)
			{
				continue;
			}

			//Wrapping the ship and adding friction
			if (p_sp->m_type == SPACESHIP)
			{
				wrap(p_ob);
				body* ship_body = (body*)p_ob->get_component(COMPONENT_TYPE::TYPE_BODY);
				ship_body->m_vel_x= ship_body->m_vel_x*0.99;
				ship_body->m_vel_y= ship_body->m_vel_y*0.99;
			}

			if (p_sp->m_type == ENEMYBASE1)
			{
				transform* enm1_tr = (transform*)p_ob->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


				enm1_tr->m_pos_x = p_tr->m_pos_x;
				enm1_tr->m_pos_y = p_tr->m_pos_y;

				enm1_tr->m_angle =60;

				body* enm1_bdy = (body*)p_ob->get_component(COMPONENT_TYPE::TYPE_BODY);
				enm1_bdy->m_vel_x = 0.6;
				enm1_bdy->m_vel_y = 0.4;

				wrap(p_ob);
			}

			if (p_sp->m_type == ENEMYBASE2)
			{
				transform* enm1_tr = (transform*)p_ob->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


				enm1_tr->m_pos_x = p_tr->m_pos_x;
				enm1_tr->m_pos_y = p_tr->m_pos_y;

				enm1_tr->m_angle = 40;

				body* enm1_bdy = (body*)p_ob->get_component(COMPONENT_TYPE::TYPE_BODY);
				enm1_bdy->m_vel_x = 0.1;
				enm1_bdy->m_vel_y = 0.7;

				wrap(p_ob);
			}

			if (p_sp->m_type == ENEMYBASE3)
			{
				transform* enm1_tr = (transform*)p_ob->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);


				enm1_tr->m_pos_x = p_tr->m_pos_x;
				enm1_tr->m_pos_y = p_tr->m_pos_y;

				enm1_tr->m_angle = 10;

				body* enm1_bdy = (body*)p_ob->get_component(COMPONENT_TYPE::TYPE_BODY);
				enm1_bdy->m_vel_x = 0.2;
				enm1_bdy->m_vel_y = 0.5
					;

				wrap(p_ob);
			}

			//Passing values to the shader
			GLuint transformLoc = glGetUniformLocation(shader.Program, "transform");
			glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(p_tr->m_p_transform));


			//Draw Object
			p_sp->draw_mesh();

		}

		glfwPollEvents();
		SDL_GL_SwapWindow(pWindow);
		p_frc->frame_end();
	}

	delete p_pm;
	delete p_frc;
	delete p_im;
	delete p_rm;
	delete p_gom;
	delete p_em;

	SDL_GL_DeleteContext(mainContext);


	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;

}

void wrap(game_object* p_go)
{
	transform* p_tr = (transform*)p_go->get_component(COMPONENT_TYPE::TYPE_TRANSFORM);

	if (p_tr->m_pos_x > 1.1f || p_tr->m_pos_x < -1.1f)
	{

		p_tr->m_pos_x = -p_tr->m_pos_x;

	}

	if (p_tr->m_pos_y > 1.1f || p_tr->m_pos_y < -1.1f)
	{

		p_tr->m_pos_y = -p_tr->m_pos_y;

	}

}