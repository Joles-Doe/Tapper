#pragma once
#include "GameObject.h"
class Background : public GameObject
{
public:
	Background(SDL_Renderer* _rend) : GameObject(_rend) {};
	void Update(SDL_Event e);
};

