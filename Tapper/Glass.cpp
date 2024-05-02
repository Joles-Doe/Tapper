#include "Glass.h"

void Glass::Update()
{
	dstRect.x += direction;

	if (dstRect.x <= 0)
	{
		destroy = true;
	}
}
