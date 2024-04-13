#include "Background.h"

void Background::Update(SDL_Event e)
{
	SDL_RenderCopy(renderer, imageTexture, &srcRect, &dstRect);
}
