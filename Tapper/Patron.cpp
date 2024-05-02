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
				idleTimer = IdleTimerStart();
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
						idleTimer = IdleTimerStart();
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
		dstRect.x -= 3;
	}


	if (dstRect.x < -200 && canLeave == true)
	{
		destroy = true;
	}
}

Uint64 Patron::IdleTimerStart()
{
	return SDL_GetTicks();
}

bool Patron::CheckIdle()
{
	int x = rand() % 3;
	return x == 2;
}
