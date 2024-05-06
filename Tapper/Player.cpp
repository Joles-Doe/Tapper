#include "Player.h"

void Player::Update()
{
	animation_ChangeToIdle = true;
	//Left and right movement
	if (controller->GetKeyDown("a") || controller->GetKeyDown("left"))
	{
		dstRect.x -= 2;
		animation_ChangeToMove = true;
		animation_ChangeToIdle = false;
	}
	if (controller->GetKeyDown("d") || controller->GetKeyDown("right"))
	{
		dstRect.x += 2;
		animation_ChangeToMove = true;
		animation_ChangeToIdle = false;
	}
	//Left and right clamping
	if (dstRect.x <= 38)
	{
		if (animation_ChangeToMove == true)
		{
			animation_ChangeToMove = false;
			animation_ChangeToIdle = true;
		}
		dstRect.x = 38;
	}
	if (dstRect.x >= 776)
	{
		if (animation_ChangeToMove == true)
		{
			animation_ChangeToMove = false;
			animation_ChangeToIdle = true;
		}
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
		if (SDL_GetTicks() >= yTicks + 500)
		{
			endTimerY();
		}
	}

	//Spacebar interaction
	if (controller->GetKeyDown("spacebar"))
	{
		if (spaceTimer != true)
		{
			if (dstRect.x >= 776)
			{
				spaceTicks = startTimerSpace();
			}
		}
		if (dstRect.x >= 776)
		{
			animation_ChangeToPour = true;
			animation_ChangeToIdle = false;
		}
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

void Player::Draw()
{
	SpriteUpdate();
	if (animationColumn != 3)
	{
		SDL_RenderCopyEx(renderer, imageTexture, &srcRect, &dstRect, 0, NULL, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		SDL_RenderCopy(renderer, imageTexture, &srcRect, &dstRect);
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

void Player::SpriteUpdate()
{
	/*
	column = 64 * iterator
	idle = 40 x 56 (distance between sprites - 64 * iterator)
	walking = 44 x 56 (distance between sprites - 64 * iterator)
	drinking = 52 x 56 (single sprite)
	pouring = 64 x 56 (distance between sprites - 64 * iterator)
	death = 52 x 56 (single sprite)*/

	if (animation_ChangeToIdle == true)
	{
		//check if animation is the same
		if (animationColumn != 0)
		{
			animationSingleSprite = false;
			animation_ChangeToIdle = false;
			srcRect.w = 44;
			dstRect.w = 44 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationColumn = 0;
			animationStep = 0;
			animationMaxSteps = 3;
			animationTimer = SDL_GetTicks();
			animationDelay = 250;
		}
	}
	if (animation_ChangeToMove == true)
	{
		if (animationColumn != 1)
		{
			animationSingleSprite = false;
			animation_ChangeToMove = false;
			srcRect.w = 44;
			dstRect.w = 44 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationColumn = 1;
			animationStep = 0;
			animationMaxSteps = 3;
			animationTimer = SDL_GetTicks();
			animationDelay = 250;
		}
	}
	if (animation_ChangeToDrink == true)
	{
		if (animationColumn != 2)
		{
			animationSingleSprite = true;
			animation_ChangeToDrink = false;
			srcRect.w = 52;
			dstRect.w = 52 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationColumn = 2;
			animationStep = 0;
		}
	}
	if (animation_ChangeToPour == true)
	{
		if (animationColumn != 3)
		{
			animationSingleSprite = false;
			animation_ChangeToPour = false;
			srcRect.w = 64;
			dstRect.w = 64 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationColumn = 3;
			animationStep = 0;
			animationMaxSteps = 1;
			animationTimer = SDL_GetTicks();
			animationDelay = 700;
		}
	}
	if (animation_ChangeToDeath == true)
	{
		if (animationColumn != 4)
		{
			animationSingleSprite = true;
			animation_ChangeToDeath = false;
			srcRect.w = 52;
			dstRect.w = 52 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationColumn = 4;
			animationStep = 0;
		}
	}

	if (animationSingleSprite == false)
	{
		if (SDL_GetTicks() > animationTimer + animationDelay)
		{
			animationStep++;
			if (animationStep > animationMaxSteps)
			{
				if (animationColumn != 3)
				{
					animationStep = 0;
				}
				else
				{
					animationStep = 1;
				}
			}
			animationTimer = SDL_GetTicks();
			
		}
	}
	srcRect.x = 64 * animationStep;
	srcRect.y = 64 * animationColumn;
}