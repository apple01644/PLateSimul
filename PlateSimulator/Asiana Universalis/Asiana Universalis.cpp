#include <SDL.h>
#include "stdafx.h"
#include <cstdlib>
#include "Map.h"
#include "Util.h"

SDL_Renderer* SDL_CreateRenderer(SDL_Window* window,
	int         index,
	Uint32      flags);

int main(int argc, char** argv)
{
	SDL_Window* window = NULL;
	window = SDL_CreateWindow
	(
		"Holy Sheet", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1600,
		960,
		SDL_WINDOW_SHOWN
	);

	Map* m_Map;
	m_Map = new Map;
	m_Map->INIT();

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	unsigned int k;
	SDL_Rect r;
	r.x = 0;
	r.y = 0;
	r.w = 1;
	r.h = 1;
	SDL_Event EVT;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&EVT) != 0)
		{
			if (EVT.type == SDL_QUIT)
			{
				quit = true;
			}
			else if (EVT.type == SDL_KEYDOWN)
			{
				//Select surfaces based on key press
				switch (EVT.key.keysym.sym)
				{
					case SDLK_ESCAPE:{
						quit = true;
							break;
					}
					default:
						k = EVT.key.keysym.sym;
						m_Map->KEY(k);
						break;
				}
			}
		}

		//#pragma loop(hint_parallel(48))  
		for (int a = 0; a < 200; a += 1)
		{
			for (int b = 0; b < 160; b += 1)
			{
				if (a < 200 && b < 160)
				{
					SDL_SetRenderDrawColor(renderer, m_Map->GET_RECT(a,b,0), m_Map->GET_RECT(a, b, 1), m_Map->GET_RECT(a, b, 2), 255);
					r.x = a * 8;
					r.y = b * 8;
					r.w = 8;
					r.h = 8;
					SDL_RenderFillRect(renderer, &r);


				}
				//SDL_RenderPresent(renderer);
			}
		}
		SDL_RenderPresent(renderer);
		m_Map->STEP();
	}


	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}