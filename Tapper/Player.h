#pragma once
#include "GameObject.h"
#include "EventController.h"

class Player : public GameObject
{
private:
	EventController* controller{ nullptr };

	int yIndex{ 0 };
	int yPositions[3]{200, 440, 685};
	bool yTimer{ false };
	Uint64 yTicks{ 0 };
	Uint64 startTimerY();
	void endTimerY();

	int counterEndPos{ 776 };
public:
	Player(SDL_Renderer* _rend, EventController* _controller) : GameObject(_rend) {
		SetRectScale(75, 175);
		SetRectPos(counterEndPos, 200);
		controller = _controller;
	};

	void Update();

	void SetController(EventController* _controller);
};

