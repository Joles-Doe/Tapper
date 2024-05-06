#include "Patron.h"

void Patron::Update()
{
	//If statement to determine whether to move left or right
	if (canLeave == false)
	{
		//If true, pause for a second
		if (idle == true)
		{
			animation_ChangeToIdle = true;
			if (SDL_GetTicks() > idleTimer + 1000)
			{
				idle = false;
				resetIdleTimer = true;
			}
		}
		else
		{
			//If true, reset timer
			if (resetIdleTimer == true)
			{
				idleTimer = TimerStart();
				resetIdleTimer = false;
			}
			else
			{
				//Once the timer reaches two seconds
				if (SDL_GetTicks() > idleTimer + 2000)
				{
					//Check if patron should start idling
					if (CheckIdle() == true)
					{
						idle = true;
						//Reset timer for idling sequence
						idleTimer = TimerStart();
					}
					//Else, reset the timer again
					else
					{
						resetIdleTimer = true;
					}
				}
			}
			animation_ChangeToMove = true;
			dstRect.x += 1;
		}
	}
	else
	{
		//If true, pause to drink
		if (drink == true)
		{
			animation_ChangeToDrink = true;
			if (SDL_GetTicks() > drinkTimer + 2000)
			{
				drink = false;
				resetDrinkTimer = true;
				canLeave = false;
				returnDrink = true;
			}
		}
		else
		{
			//If true, reset timer
			if (resetDrinkTimer == true)
			{
				drinkTimer = TimerStart();
				resetDrinkTimer = false;
			}
			else
			{
				//Check if patron is still on screen
				if (dstRect.x > 0)
				{
					//Once the timer reaches two seconds
					if (SDL_GetTicks() > drinkTimer + 1200)
					{
						//Check if patron should start drinking
						if (CheckDrink() == true)
						{
							drink = true;
							//Reset timer for drinking sequence
							drinkTimer = TimerStart();
						}
						//Else, reset the timer again
						else
						{
							resetDrinkTimer = true;
						}
					}
				}
			}
			animation_ChangeToReturn = true;
			dstRect.x -= 3;
		}
	}

	if (dstRect.x < -200 && canLeave == true)
	{
		destroy = true;
	}
	else if (dstRect.x > 776)
	{
		reachedEnd = true;
	}
}

void Patron::Draw()
{
	SpriteUpdate();
	SDL_RenderCopy(renderer, imageTexture, &srcRect, &dstRect);
}

Uint64 Patron::TimerStart()
{
	return SDL_GetTicks();
}

bool Patron::CheckIdle()
{
	int x = rand() % 3;
	return x == 2;
}

bool Patron::CheckDrink()
{
	int x = rand() % 3;
	return x == 2;
}

void Patron::SpriteUpdate()
{
	/*
	column = 64 * iterator
	idle = 40 x 56 (distance between sprites - 64 * iterator)
	walking = 44 x 56 (distance between sprites - 64 * iterator)
	drinking = 52 x 56 (single sprite)
	leaving = 64 x 56 (single sprite)*/

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
	if (animation_ChangeToReturn == true)
	{
		if (animationColumn != 3)
		{
			animationSingleSprite = true;
			animation_ChangeToReturn = false;
			srcRect.w = 64;
			dstRect.w = 64 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationColumn = 3;
			animationStep = 0;
		}
	}

	if (animationSingleSprite == false)
	{
		if (SDL_GetTicks() > animationTimer + animationDelay)
		{
			animationStep++;
			if (animationStep >= animationMaxSteps)
			{
				animationStep = 0;
			}
			animationTimer = SDL_GetTicks();
			srcRect.x = 64 * animationStep;
			srcRect.y = 64 * animationColumn;
		}
	}
	else
	{
		srcRect.x = 0;
		srcRect.y = 64 * animationColumn;
	}
}
