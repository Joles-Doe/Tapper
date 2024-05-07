#pragma once
#include "GameObject.h"

class Glass : public GameObject
{
private:
	//Predefined counter positions
	int counterPositions[3]{ 247, 490, 735 };
	//Direction variable - gets given a positive or negative value dependent on the direction it's travelling
	int direction{ 0 };
	bool moveLeft{ false };
	bool glassReachedEnd{ false };
public:
	Glass(SDL_Renderer* _rend, int _posX, int _indexY, const std::string& _direction) : GameObject(_rend) {
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
	//Returns the moveLeft variable
	bool GetMoveLeft() { return moveLeft; }
	//Returns the reachedEnd variable
	bool GetGlassEnd() { return glassReachedEnd; }

	void Update();
};

