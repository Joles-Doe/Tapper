#pragma once
#include "GameObject.h"

class Glass : public GameObject
{
private:
	int counterPositions[3]{ 282, 525, 770 };
	int direction{ 0 };
public:
	Glass(SDL_Renderer* _rend, int _posX, int _indexY, const std::string& _direction) : GameObject(_rend) {
		SetRectScale(50, 50);
		SetRectPos(_posX, counterPositions[_indexY]);
		if (_direction == "L" || _direction == "l" || _direction == "LEFT" || _direction == "left")
		{
			direction = -2;
		}
		else
		{
			direction = 2;
		}
	}

	void Update();
};

