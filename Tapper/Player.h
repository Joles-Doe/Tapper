#pragma once
#include "GameObject.h"
#include "Engine.h"
#include "EventController.h"
#include "Glass.h"

class Player : public GameObject
{
private:
	Engine* engine{ nullptr };
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

	std::vector<std::shared_ptr<Glass>> glassVector{ 0 };

public:
	Player(SDL_Renderer* _rend, EventController* _controller, Engine* _engine) : GameObject(_rend) {
		SetRectScale(75, 175);
		SetRectPos(counterEndPos, 200);
		engine = _engine;
		controller = _controller;
	};

	void Update();
};

