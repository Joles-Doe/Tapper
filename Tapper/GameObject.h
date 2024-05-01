#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <vector>

class GameObject
{
protected:
	SDL_Renderer* renderer{ nullptr };
	SDL_Texture* imageTexture{ nullptr };
	SDL_Rect srcRect{ 0 };
	SDL_Rect dstRect{ 0 };
	int xVelocity{ 0 };
	int yVelocity{ 0 };
public:
	GameObject(SDL_Renderer* _rend);

	//Loads a bitmap image
	void LoadImage(const std::string& _input);
	
	//Sets position of the rect. Use value -1 to keep previous value
	void SetRectPos(int _x, int _y);
	//Sets dimensions of the rect. Use value -1 to keep previous value
	void SetRectScale(int _w, int _h);

	//Runs once per frame
	virtual void Update() = 0;

	virtual void Draw();
};