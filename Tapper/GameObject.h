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
	bool destroy{ 0 };
public:
	GameObject(SDL_Renderer* _rend);

	//Loads a bitmap image
	void LoadImage(const std::string& _input);
	
	//Sets position of the rect. Use value -1 to keep previous value
	void SetRectPos(int _x, int _y);
	//Sets dimensions of the rect. Use value -1 to keep previous value
	void SetRectScale(int _w, int _h);
	//Gets X value of the rect.
	int GetRectX();
	//Gets Y value of the rect.
	int GetRectY();


	//Returns the destroy variable
	bool GetDestroy();

	//Runs once per frame
	virtual void Update() = 0;

	virtual void Draw();
};