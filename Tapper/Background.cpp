#include "Background.h"

void Background::Update()
{
	SDL_RenderCopy(renderer, imageTexture, &srcRect, &dstRect);
}
