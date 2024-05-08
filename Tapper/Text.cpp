#include "Text.h"

Text::~Text()
{
	TTF_CloseFont(font);
}

void Text::ChangeColor(int _r, int _g, int _b)
{
	if (_r != -1)
	{
		color.r = _r;
	}
	if (_g != -1)
	{
		color.g = _g;
	}
	if (_b != -1)
	{
		color.b = _b;
	}
}

void Text::ChangeText(const std::string& _text)
{
	//Creates a surface that will contain the text
	SDL_Surface* textSurface;
	//Draws the text onto the surface
	textSurface = TTF_RenderText_Solid(font, _text.c_str(), color);
	if (!textSurface)
	{
		std::cout << "Text render FAILED " << TTF_GetError() << std::endl;
	}

	//If the surface returns null, return an error
	if (textSurface == nullptr)
	{
		std::cout << "Failed to load surface TTF " << SDL_GetError() << std::endl;
	}
	else
	{
		//Checks if a texture for the object already exists, and purges it if so
		if (imageTexture != nullptr)
		{
			SDL_DestroyTexture(imageTexture);
		}
		//Create a texture from the surface
		imageTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		//Free the surface from memory
		SDL_FreeSurface(textSurface);
		//Set rect sizes to image size
		SDL_QueryTexture(imageTexture, 0, 0, &srcRect.w, &srcRect.h);
		dstRect.w = srcRect.w;
		dstRect.h = srcRect.h;
	}
}