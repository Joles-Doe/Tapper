#include <SDL.h>
#include "Engine.h"
#include "GameObject.h"
#include "Background.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	srand(time(0));
	
	const int FPS{ 60 };
	const float frameDelay{ 1000 / FPS };

	Engine sdlEngine = Engine();
	SDL_Event e;

	std::shared_ptr<Background> floor = std::make_shared<Background>(sdlEngine.GetRenderer());
	floor->LoadImage("Floor.bmp");
	sdlEngine.AddLayerElement(floor, 0);

	std::shared_ptr<Background> backWall = std::make_shared<Background>(sdlEngine.GetRenderer());
	backWall->LoadImage("Back Wall.bmp");
	sdlEngine.AddLayerElement(backWall, 1);

	std::shared_ptr<Background> barCounters = std::make_shared<Background>(sdlEngine.GetRenderer());
	barCounters->LoadImage("Counters.bmp");
	sdlEngine.AddLayerElement(barCounters, 3);

	std::shared_ptr<Background> sideWall = std::make_shared<Background>(sdlEngine.GetRenderer());
	sideWall->LoadImage("Side Wall.bmp");
	sdlEngine.AddLayerElement(sideWall, 5);

	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };

	bool loop = true;
	while (loop)
	{
		frameStart = SDL_GetTicks();

		sdlEngine.Reset();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				loop = false;
			}
		}
		sdlEngine.Update(e);
		sdlEngine.Present();
		
		frameEnd = SDL_GetTicks();
		std::cout << (frameEnd - frameStart) << std::endl;
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	return 0;
}