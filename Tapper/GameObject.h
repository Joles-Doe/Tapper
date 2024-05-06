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

	int velocity[2]{ 0, 0 };
	bool destroy{ false	 };
	bool visible{ true };
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

	//Gets the Rect of the object
	SDL_Rect GetRect() { return dstRect; }

	//Returns the destroy variable
	bool GetDestroy();
	//Sets the destroy variable
	void SetDestroy(bool _destroy) { destroy = _destroy; }

	//Returns the visible variable
	bool GetVisible() { return visible; }
	//Sets the visible variable
	void SetVisible(bool _visible) { visible = _visible; }

	int GetVelocityX() { return velocity[0]; }
	int GetVelocityY() { return velocity[1]; }

	void SetVelocityX(int _velX) { velocity[0] = _velX; }
	void SetVelocityY(int _velY) { velocity[1] = _velY; }

	//Runs once per frame
	virtual void Update() = 0;

	virtual void Draw();
};