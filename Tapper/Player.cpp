#include "Player.h"

void Player::Update()
{
	//Change to idle animation
	animation_ChangeToIdle = true;
	//If the player can act
	if (canAct == true)
	{
		//Movement
		//Left and right movement
		if (controller->GetKeyDown("a") || controller->GetKeyDown("left"))
		{
			dstRect.x -= 2;
			//Change to the move animation - set the idle animation to false
			animation_ChangeToMove = true;
			animation_ChangeToIdle = false;
		}
		if (controller->GetKeyDown("d") || controller->GetKeyDown("right"))
		{
			dstRect.x += 2;
			//Change to the move animation - set the idle animation to false
			animation_ChangeToMove = true;
			animation_ChangeToIdle = false;
		}
		//Left and right clamping
		if (dstRect.x <= 38)
		{
			//If the animation is the move animation, change back to idle
			if (animation_ChangeToMove == true)
			{
				animation_ChangeToMove = false;
				animation_ChangeToIdle = true;
			}
			dstRect.x = 38;
		}
		if (dstRect.x >= 776)
		{
			//If the animation is the move animation, change back to idle
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
				//Change the Y Index
				if (yIndex == 0)
				{
					yIndex = 2;
				}
				else
				{
					yIndex--;
				}
				//Begin the delay for upwards and downwards movement
				yTicks = startTimerY();
				dstRect.y = yPositions[yIndex];
				dstRect.x = counterEndPos;
				//Stop the pouring timer
				EndTimerSpace();
			}
			if (controller->GetKeyDown("s") || controller->GetKeyDown("down"))
			{
				//Change the Y Index
				if (yIndex == 2)
				{
					yIndex = 0;
				}
				else
				{
					yIndex++;
				}
				//Begin the delay for upwards and downwards movement
				yTicks = startTimerY();
				dstRect.y = yPositions[yIndex];
				dstRect.x = counterEndPos;
				//Stop the pouring timer
				EndTimerSpace();
			}
		}
		else
		{
			//Once half a second has passed, allow upwards and downwards movement
			if (SDL_GetTicks() >= yTicks + 500)
			{
				endTimerY();
			}
		}

		//Pouring action
		if (controller->GetKeyDown("spacebar"))
		{
			if (spaceTimer != true)
			{
				//If the player is at the end of the bar
				if (dstRect.x >= counterEndPos)
				{
					//Begin the pouring timer
					spaceTicks = StartTimerSpace();
				}
			}
			if (dstRect.x >= counterEndPos)
			{
				//Change animation to pouring, and disable the idle animation
				animation_ChangeToPour = true;
				animation_ChangeToIdle = false;
			}
		}
		//Upon spacebar keyup
		else
		{
			//If the player has been pouring previously
			if (spaceTimer == true)
			{
				//Check if the glass can be thrown
				if (SDL_GetTicks() >= spaceTicks + 700)
				{
					//Create a new glass
					std::shared_ptr<Glass> currentGlass = std::make_shared<Glass>(renderer, dstRect.x, yIndex, "l");
					currentGlass->LoadImage("GlassPlaceholder.bmp");
					newGlass = true;
				}
			}
			//End the timer
			EndTimerSpace();
		}
	}
}

void Player::Draw()
{
	SpriteUpdate();
	if (animationRow != 3)
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

Uint64 Player::startTimerY()
{
	yTimer = true;
	return SDL_GetTicks();
}

void Player::endTimerY()
{
	yTimer = false;
}

Uint64 Player::StartTimerSpace()
{
	spaceTimer = true;
	return SDL_GetTicks();
}

void Player::EndTimerSpace()
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
	death = 52 x 56 (single sprite)
	*/

	if (animation_ChangeToIdle == true)
	{
		//Check if animation is the same
		if (animationRow != 0)
		{
			animationSingleSprite = false;
			animation_ChangeToIdle = false;
			//Set width and height of both the dstRect and srcRect
			srcRect.w = 44;
			dstRect.w = 44 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			//Set the row
			animationRow = 0;
			//Set the step to 0
			animationStep = 0;
			//Set max steps
			animationMaxSteps = 3;
			//Begin the timer and set the delay
			animationTimer = SDL_GetTicks();
			animationDelay = 250;
		}
	}
	if (animation_ChangeToMove == true)
	{
		if (animationRow != 1)
		{
			animationSingleSprite = false;
			animation_ChangeToMove = false;
			srcRect.w = 44;
			dstRect.w = 44 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationRow = 1;
			animationStep = 0;
			animationMaxSteps = 3;
			animationTimer = SDL_GetTicks();
			animationDelay = 250;
		}
	}
	if (animation_ChangeToDrink == true)
	{
		if (animationRow != 2)
		{
			animationSingleSprite = true;
			animation_ChangeToDrink = false;
			srcRect.w = 52;
			dstRect.w = 52 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationRow = 2;
			animationStep = 0;
		}
	}
	if (animation_ChangeToPour == true)
	{
		if (animationRow != 3)
		{
			animationSingleSprite = false;
			animation_ChangeToPour = false;
			srcRect.w = 64;
			dstRect.w = 64 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationRow = 3;
			animationStep = 0;
			animationMaxSteps = 1;
			animationTimer = SDL_GetTicks();
			animationDelay = 700;
		}
	}
	if (animation_ChangeToDeath == true)
	{
		if (animationRow != 4)
		{
			animationSingleSprite = true;
			animation_ChangeToDeath = false;
			srcRect.w = 52;
			dstRect.w = 52 * 2;
			srcRect.h = 56;
			dstRect.h = 56 * 2;
			animationRow = 4;
			animationStep = 0;
		}
	}

	//Check if the sprite should animate
	if (animationSingleSprite == false)
	{
		//Once the sprite has exceeded the delay threshold
		if (SDL_GetTicks() > animationTimer + animationDelay)
		{
			//Move to the next frame in the animation
			animationStep++;
			//If the step has reached the max steps, loop the animation, UNLESS its the pouring animation
			if (animationStep > animationMaxSteps)
			{
				if (animationRow != 3)
				{
					animationStep = 0;
				}
				else
				{
					animationStep = 1;
				}
			}
			//Reset timer
			animationTimer = SDL_GetTicks();
			
		}
	}
	//Set the src rect dimensions
	srcRect.x = 64 * animationStep;
	srcRect.y = 64 * animationRow;
}