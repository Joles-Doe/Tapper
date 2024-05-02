#pragma once
#include "GameObject.h"

class Patron : public GameObject
{
private:
	int yPositions[3]{ 200, 440, 685 };

	bool canLeave{ false };

	bool idle{ false };
	bool resetIdleTimer{ true };
	Uint64 idleTimer{ 0 };

public:
	Patron(SDL_Renderer* _rend, int _indexY) : GameObject(_rend) {
		SetRectScale(75, 175);
		SetRectPos(-150, yPositions[_indexY]);
	}

	void Update();

	void SetLeave(bool _input) { canLeave = _input; }

	Uint64 IdleTimerStart();
	void IdleTimerEnd();
	bool CheckIdle();
};

