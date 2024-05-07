#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* _rend)
{
	renderer = _rend;
}

void GameObject::LoadImage(const std::string &_input)
{
	//Creates a surface from the image path
	SDL_Surface* imageSurface = SDL_LoadBMP(_input.c_str());
	//If the surface returns null, return an error
	if (imageSurface == nullptr)
	{
		std::cout << "Failed to load image " << _input << " " << SDL_GetError();
	}
	else
	{
		//Checks if a texture for the object already exists, and purges it if so
		if (imageTexture != nullptr)
		{
			SDL_DestroyTexture(imageTexture);
		}
		//Create a texture from the surface
		imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
		//Free the surface from memory
		SDL_FreeSurface(imageSurface);
		//Set rect sizes to image size
		SDL_QueryTexture(imageTexture, 0, 0, &srcRect.w, &srcRect.h);
		dstRect.w = srcRect.w;
		dstRect.h = srcRect.h;
	}
}

void GameObject::SetRectPos(int _x, int _y)
{
	if (_x != -1)
	{
		dstRect.x = _x;
	}
	if (_y != -1)
	{
		dstRect.y = _y;
	}
}

void GameObject::SetRectScale(int _w, int _h)
{
	if (_w != -1)
	{
		dstRect.w = _w;
	}
	if (_h != -1)
	{
		dstRect.h = _h;
	}
}

void GameObject::Draw()
{
	if (visible == true)
	{
		SDL_RenderCopy(renderer, imageTexture, &srcRect, &dstRect);
	}
}
