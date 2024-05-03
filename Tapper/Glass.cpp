#include "Glass.h"

void Glass::Update()
{
	dstRect.x += direction;

	if (dstRect.x <= 0)
	{
		glassReachedEnd = true;
		destroy = true;
	}
	else if (dstRect.x > 776)
	{
		glassReachedEnd = true;
		destroy = true;
	}
}
