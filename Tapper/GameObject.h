#pragma once
#include <string>
#include <iostream>
#include <SDL.h>
#include <vector>

//Abstract class - only use for inheritance
class GameObject
{
protected:
	SDL_Renderer* renderer{ nullptr };
	SDL_Texture* imageTexture{ nullptr };
	SDL_Rect srcRect{ 0 };
	SDL_Rect dstRect{ 0 };

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
	//Gets X value of the rect 
	int GetRectX() { return dstRect.x; }
	//Gets Y value of the rect
	int GetRectY() { return dstRect.y; }

	//Gets the Rect of the object
	SDL_Rect GetRect() { return dstRect; }

	//Getters and Setters for the destroy variable
	bool GetDestroy() { return destroy; }
	void SetDestroy(bool _destroy) { destroy = _destroy; }

	//Getters and Setters for the visible variable
	bool GetVisible() { return visible; }
	void SetVisible(bool _visible) { visible = _visible; }

	//Runs once per frame - virtual functions
	virtual void Update() = 0; //Pure virtual - must be redefined in derived classes
	virtual void Draw();
};