#include "Player.h"

void Player::Update()
{
	//Left and right movement
	if (controller->GetKeyDown("a") || controller->GetKeyDown("left"))
	{
		dstRect.x -= 2;
	}
	if (controller->GetKeyDown("d") || controller->GetKeyDown("right"))
	{
		dstRect.x += 2;
	}
	//Left and right clamping
	if (dstRect.x <= 38)
	{
		dstRect.x = 38;
	}
	if (dstRect.x >= 776)
	{
		dstRect.x = counterEndPos;
	}

	//Up and down movement - delayed by a timer to prevent instantaneously moving from top to bottom
	if (yTimer != true)
	{
		if (controller->GetKeyDown("w") || controller->GetKeyDown("up"))
		{
			if (yIndex == 0)
			{
				yIndex = 2;
			}
			else
			{
				yIndex--;
			}
			yTicks = startTimerY();
			dstRect.y = yPositions[yIndex];
			dstRect.x = counterEndPos;
		}
		if (controller->GetKeyDown("s") || controller->GetKeyDown("down"))
		{
			if (yIndex == 2)
			{
				yIndex = 0;
			}
			else
			{
				yIndex++;
			}
			yTicks = startTimerY();
			dstRect.y = yPositions[yIndex];
			dstRect.x = counterEndPos;
		}
	}
	else
	{
		if (SDL_GetTicks() >= yTicks + 700)
		{
			endTimerY();
		}
	}

	//Spacebar interaction
}

void Player::SetController(EventController* _controller)
{
	controller = _controller;
	return;
}

Uint64 Player::startTimerY()
{
	yTimer = true;
	return SDL_GetTicks();
}

void Player::endTimerY()
{
	yTimer = false;
}