#include "Glass.h"

void Glass::Update()
{
	//Move in the defined direction
	dstRect.x += direction;

	//If the glass has reached either end of the counter
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
