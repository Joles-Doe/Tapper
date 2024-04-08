#include <SDL.h>
#include <iostream>
#include <string>



int main(int argc, char* argv[])
{
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window{ nullptr };
	SDL_Renderer* rend{ nullptr };
	int window_w = 1000;
	int window_h = 700;
	window = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "Window creation FAILED " << SDL_GetError();
	}

	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (rend == nullptr)
	{
		std::cout << "Renderer creation FAILED " << SDL_GetError();
	}
	SDL_RenderSetLogicalSize(rend, window_w, window_h);

	SDL_Event e;

	bool loop = true;
	while (loop)
	{
		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
		SDL_RenderClear(rend);

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				loop = false;
			}
		}
		SDL_RenderPresent(rend);
	}


	return 0;
}