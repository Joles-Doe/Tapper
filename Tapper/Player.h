#pragma once
#include "GameObject.h"
#include "EventController.h"

class Player : public GameObject
{
private:
	EventController* controller{ nullptr };
public:
	Player(SDL_Renderer* _rend, EventController* _controller) : GameObject(_rend) {
		SetRectScale(75, 175);
		SetRectPos(200, 200);
		controller = _controller;
	};

	void Update();

	void SetController(EventController* _controller);
};

