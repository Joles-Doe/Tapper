#pragma once
#include "GameObject.h"

class Patron : public GameObject
{
private:
	//Predefined Y positions
	int yPositions[3]{ 200, 440, 685 };
	int yIndex{ 0 };

	//Determines whether the instance moves left or right
	bool canLeave{ false };
	//If set to true, the instance has reached the end of the counter
	bool reachedEnd{ false };

	//Returns current time
	Uint64 TimerStart() { return SDL_GetTicks(); }

	//Idle behaviour variables
	bool idle{ false };
	bool resetIdleTimer{ true };
	Uint64 idleTimer{ 0 };
	bool CheckIdle();
	//Drink behaviour variables
	bool drink{ false };
	bool returnDrink{ false };
	bool resetDrinkTimer{ true };
	Uint64 drinkTimer{ 0 };
	bool CheckDrink();

	//Sprite variables
	//Changes animation if specified
	void SpriteUpdate();
	SDL_Rect srcRect{ 0 };
	bool animation_ChangeToMove{ true };
	bool animation_ChangeToDrink{ false };
	bool animation_ChangeToIdle{ false };
	bool animation_ChangeToReturn{ false };
	bool animationSingleSprite{ false };
	int animationRow{ 0 };
	Uint64 animationTimer{ 0 };
	int animationDelay{ 0 };
	int animationStep{ 0 };
	int animationMaxSteps{ 0 };
public:
	Patron(SDL_Renderer* _rend, int _indexY) : GameObject(_rend) {
		SetRectScale(75, 175);
		SetRectPos(-150, yPositions[_indexY]);
		yIndex = _indexY;
	}

	void Update();
	void Draw();

	//Getters and Setters for the canLeave variable
	bool GetLeave() { return canLeave; }
	void SetLeave(bool _input) { canLeave = _input; }
	//Getters and Setters for the returnDrink variable
	bool GetReturnDrink() { return returnDrink; }
	void SetReturnDrink(bool _return) { returnDrink = _return; }
	//Returns the reachedEnd variable
	bool GetReachedEnd() { return reachedEnd; }
	//Returns the Y index
	int GetYIndex() { return yIndex; }
};