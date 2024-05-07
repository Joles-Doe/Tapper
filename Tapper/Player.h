#pragma once
#include "GameObject.h"
#include "EventController.h"
#include "Glass.h"

class Player : public GameObject
{
private:
	//Controller
	EventController* controller{ nullptr };
	//Y index and predefined positions
	int yIndex{ 0 };
	int yPositions[3]{200, 440, 685};
	//Variables related to delaying the player's up and down movement
	bool yTimer{ false };
	Uint64 yTicks{ 0 };
	Uint64 startTimerY();
	void endTimerY();

	//Determines whether or not the player can do anything
	bool canAct{ false };

	//Variables related to the pouring action
	Uint64 StartTimerSpace();
	void EndTimerSpace();
	bool canThrow{ false };
	bool spaceTimer{ false };
	Uint64 spaceTicks{ 0 };

	//Contains the x position of the end of the bar counters
	int counterEndPos{ 776 };

	//Variables related to creating glasses
	std::shared_ptr<Glass> currentGlass{ 0 };
	bool newGlass{ false };

	//Variables related to animation
	void SpriteUpdate();
	SDL_Rect srcRect{ 0 };
	bool animation_ChangeToMove{ false };
	bool animation_ChangeToDrink{ false };
	bool animation_ChangeToIdle{ true };
	bool animation_ChangeToPour{ false };
	bool animation_ChangeToDeath{ false };
	bool animationSingleSprite{ false };
	int animationRow{ 9 };
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
	std::shared_ptr<Glass> GetGlass() { return currentGlass; }

	//Getters and Setters for the canAct variable
	int GetAct() { return canAct; }
	void SetAct(bool _act) { canAct = _act; }
	//Returns the Y Index
	int GetYIndex() { return yIndex; }
};