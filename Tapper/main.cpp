#include <SDL.h>
#include "Engine.h"
#include "GameObject.h"
#include "Background.h"
#include "Player.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	srand(time(0));
	
	const int FPS{ 60 };
	const float frameDelay{ 1000 / FPS };

	Engine sdlEngine = Engine();

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

	std::shared_ptr<Player> player = std::make_shared<Player>(sdlEngine.GetRenderer(), sdlEngine.GetController());
	player->LoadImage("PlayerPlaceholder.bmp");
	sdlEngine.AddLayerElement(player, 2);


	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };
	sdlEngine.SetLoopState(true);
	while (sdlEngine.GetLoopState())
	{
		frameStart = SDL_GetTicks();
		
		sdlEngine.Reset();
		sdlEngine.ControllerPollEvents();
		sdlEngine.Update();
		sdlEngine.Present();
		
		frameEnd = SDL_GetTicks();
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	return 0;
}