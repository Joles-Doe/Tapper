#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(SDL_Renderer* _rend) : GameObject(_rend) {};
	void Update();
};

