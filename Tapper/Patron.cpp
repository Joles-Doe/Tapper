#include "Patron.h"

void Patron::Update()
{
	//If statement to determine whether to move left or right
	if (canLeave == false)
	{
		//If true, pause for a second
		if (idle == true)
		{
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
			dstRect.x += 1;
		}
	}
	else
	{
		//If true, pause to drink
		if (drink == true)
		{
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
			dstRect.x -= 3;
		}
	}


	if (dstRect.x < -200 && canLeave == true)
	{
		destroy = true;
	}
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