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

			endTimerSpace();
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

			endTimerSpace();
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
	if (controller->GetKeyDown("spacebar"))
	{
		if (spaceTimer != true)
		{
			spaceTicks = startTimerSpace();
		}
		std::cout << (SDL_GetTicks() >= spaceTicks + 700) << std::endl;
	}
	else
	{
		if (spaceTimer == true)
		{
			if (SDL_GetTicks() >= spaceTicks + 700)
			{
				std::shared_ptr<Glass> currentGlass = std::make_shared<Glass>(renderer, dstRect.x, yIndex, "l");
				currentGlass->LoadImage("GlassPlaceholder.bmp");
				newGlass = true;
			}
		}
		endTimerSpace();
	}
}

bool Player::CheckNewGlass()
{
	if (newGlass == true)
	{
		newGlass = false;
		return true;
	}
	else
	{
		return false;
	}
}

std::shared_ptr<Glass> Player::GetGlass()
{
	return currentGlass;
}

int Player::GetYIndex()
{
	return yIndex;
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

Uint64 Player::startTimerSpace()
{
	spaceTimer = true;
	return SDL_GetTicks();
}

void Player::endTimerSpace()
{
	spaceTimer = false;
}
