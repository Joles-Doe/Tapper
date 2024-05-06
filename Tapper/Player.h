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

	void SpriteUpdate();
	SDL_Rect srcRect{ 0 };
	bool animation_ChangeToMove{ false };
	bool animation_ChangeToDrink{ false };
	bool animation_ChangeToIdle{ true };
	bool animation_ChangeToPour{ false };
	bool animation_ChangeToDeath{ false };
	bool animationSingleSprite{ false };
	int animationColumn{ 0 };
	Uint64 animationTimer{ 0 };
	int animationDelay{ 0 };
	int animationStep{ 0 };
	int animationMaxSteps{ 0 };
public:
	Player(SDL_Renderer* _rend, EventController* _controller) : GameObject(_rend) {
		SetRectPos(counterEndPos, 200);
		controller = _controller;
	};

	void Update();
	void Draw();

	bool CheckNewGlass();
	std::shared_ptr<Glass> GetGlass();

	int GetYIndex();
};

