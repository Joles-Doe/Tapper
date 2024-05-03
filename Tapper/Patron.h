#pragma once
#include "GameObject.h"

class Patron : public GameObject
{
private:
	int yPositions[3]{ 200, 440, 685 };
	int yIndex{ 0 };

	bool canLeave{ false };
	bool reachedEnd{ false };

	Uint64 TimerStart();

	bool idle{ false };
	bool resetIdleTimer{ true };
	Uint64 idleTimer{ 0 };
	bool CheckIdle();

	bool drink{ false };
	bool returnDrink{ false };
	bool resetDrinkTimer{ true };
	Uint64 drinkTimer{ 0 };
	bool CheckDrink();
public:
	Patron(SDL_Renderer* _rend, int _indexY) : GameObject(_rend) {
		SetRectScale(75, 175);
		SetRectPos(-150, yPositions[_indexY]);
		yIndex = _indexY;
	}

	void Update();

	bool GetLeave() { return canLeave; }
	void SetLeave(bool _input) { canLeave = _input; }

	bool GetReturnDrink() { return returnDrink; }
	void SetReturnDrink(bool _return) { returnDrink = _return; }

	bool GetReachedEnd() { return reachedEnd; }

	int GetYIndex() { return yIndex; }
};