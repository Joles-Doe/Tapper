#pragma once
#include <SDL.h>
#include <vector>
class Engine
{
private:
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	int windowWidth{ 0 };
	int windowHeight{ 0 };

public:
	Engine();
	//~Engine();

	SDL_Renderer* GetRenderer();
	//void Blit(SDL_Rect _rect, int _layer);

	//Clears the renderer
	void Reset();
	//Draws the renderer to the window
	void Present();
};

