#include <SDL.h>
#include "Engine.h"
#include "GameObject.h"
#include "Background.h"
#include <iostream>
#include <string>



int main(int argc, char* argv[])
{
	srand(time(0));
	
	Engine sdlEngine = Engine();
	SDL_Event e;

	Background floor(sdlEngine.GetRenderer());
	floor.LoadImage("Floor.bmp");
	floor.SetRectPos(0, 0);

	Background backWall(sdlEngine.GetRenderer());
	backWall.LoadImage("Back Wall.bmp");
	backWall.SetRectPos(0, 0);

	Background barCounters(sdlEngine.GetRenderer());
	barCounters.LoadImage("Counters.bmp");
	barCounters.SetRectPos(0, 0);

	Background sideWall(sdlEngine.GetRenderer());
	sideWall.LoadImage("Side Wall.bmp");
	sideWall.SetRectPos(0, 0);

	bool loop = true;
	while (loop)
	{
		sdlEngine.Reset();
		floor.Update();
		backWall.Update();
		barCounters.Update();
		sideWall.Update();
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				loop = false;
			}
		}
		sdlEngine.Present();
	}


	return 0;
}