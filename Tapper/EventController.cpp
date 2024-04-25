#include "EventController.h"
#include <iostream>

void EventController::ResetVariables()
{
	keyDown = false;
	mouseDown = false;
}

void EventController::PollEvents()
{
	ResetVariables();
	while (SDL_PollEvent(&currentEvent))
	{
		switch (currentEvent.type)
		{
		//Application
		case SDL_QUIT:
			programQuit = true;
			break;
		//Keyboard
		case SDL_KEYDOWN:
			keyDown = true;
			switch (currentEvent.key.keysym.sym)
			{
			case SDLK_w:
				wDown = true;
				break;
			case SDLK_a:
				aDown = true;
				break;
			case SDLK_s:
				sDown = true;
				break;
			case SDLK_d:
				dDown = true;
				break;
			case SDLK_SPACE:
				spaceDown = true;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (currentEvent.key.keysym.sym)
			{
			case SDLK_w:
				wDown = false;
				break;
			case SDLK_a:
				aDown = false;
				std::cout << "Up" << std::endl;
				break;
			case SDLK_s:
				sDown = false;
				break;
			case SDLK_d:
				dDown = false;
				break;
			case SDLK_SPACE:
				spaceDown = false;
				break;
			}
			break;
		//Mouse
		case SDL_MOUSEBUTTONDOWN:
			mouseDown = true;
			switch (currentEvent.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse1Down = true;
				break;
			case SDL_BUTTON_RIGHT:
				mouse2Down = true;
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (currentEvent.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouse1Down = false;
				break;
			case SDL_BUTTON_RIGHT:
				mouse2Down = false;
				break;
			}
			break;
		}

	}
}

bool EventController::GetQuitState()
{
	return programQuit;
}

bool EventController::GetKeyDown(const std::string& _key)
{
	bool isDown{ false };
	if (_key == "W" || _key == "w")
	{
		isDown = wDown;
	}
	if (_key == "A" || _key == "a")
	{
		isDown = aDown;
	}
	if (_key == "S" || _key == "s")
	{
		isDown = sDown;
	}
	if (_key == "D" || _key == "d")
	{
		isDown = dDown;
	}
	if (_key == "SPACEBAR" || _key == "spacebar")
	{
		isDown = spaceDown;
	}
	return isDown;
}

bool EventController::GetKeyDown()
{
	return keyDown;
}

bool EventController::GetMouseDown(const std::string& _button)
{
	bool isDown{ false };
	if (_button == "1" || _button == "left" || _button == "LEFT")
	{
		isDown = mouse1Down;
	}
	if (_button == "2" || _button == "right" || _button == "RIGHT")
	{
		isDown = mouse2Down;
	}
	return isDown;
}

bool EventController::GetMouseDown()
{
	return mouseDown;
}
