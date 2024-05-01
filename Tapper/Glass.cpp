#include "Glass.h"

void Glass::Update()
{
	dstRect.x += direction;

	if (dstRect.x <= 40)
	{
		destroy = true;
	}
}
