#pragma once
#include "GameObject.h"

class Glass : public GameObject
{
private:
	int counterPositions[3]{ 262, 505, 750 };
	int direction{ 0 };
	bool moveLeft{ false };
	bool glassReachedEnd{ false };
public:
	Glass(SDL_Renderer* _rend, int _posX, int _indexY, const std::string& _direction) : GameObject(_rend) {
		SetRectScale(50, 50);
		SetRectPos(_posX, counterPositions[_indexY]);
		if (_direction == "L" || _direction == "l" || _direction == "LEFT" || _direction == "left")
		{
			direction = -2;
			moveLeft = true;
		}
		else
		{
			direction = 2;
		}
	}

	bool GetMoveLeft() { return moveLeft; }
	bool GetGlassEnd() { return glassReachedEnd; }

	void Update();
};

