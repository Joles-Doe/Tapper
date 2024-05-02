#pragma once
#include "GameObject.h"
#include "EventController.h"
#include "Glass.h"

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

	bool canThrow{ false };
	bool spaceTimer{ false };
	Uint64 spaceTicks{ 0 };
	Uint64 startTimerSpace();
	void endTimerSpace();

	int counterEndPos{ 776 };

	std::shared_ptr<Glass> currentGlass{ 0 };
	bool newGlass{ false };

public:
	Player(SDL_Renderer* _rend, EventController* _controller) : GameObject(_rend) {
		SetRectScale(75, 175);
		SetRectPos(counterEndPos, 200);
		controller = _controller;
	};

	void Update();

	bool CheckNewGlass();
	std::shared_ptr<Glass> GetGlass();

	int GetYIndex();
};

