#include "Player.h"

void Player::Update()
{
	if (controller->GetKeyDown("a"))
	{
		dstRect.x -= 1;
	}
	if (controller->GetKeyDown("d"))
	{
		dstRect.x += 1;
	}

	if (dstRect.x <= 0)
	{
		dstRect.x = 0;
	}
}

void Player::SetController(EventController* _controller)
{
	controller = _controller;
	return;
}
