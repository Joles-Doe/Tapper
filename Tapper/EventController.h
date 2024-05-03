#pragma once
#include <SDL.h>
#include <string>
#include <optional>
class EventController
{
private:
	SDL_Event currentEvent;

	//Resets all event variables
	void ResetVariables();

	//Event variables
	//Application
	bool programQuit{ false };
	//Keyboard
	bool keyDown{ false };
	//Keyboard specific
	bool wDown{ false };
	bool aDown{ false };
	bool sDown{ false };
	bool dDown{ false };
	bool upArrowDown{ false };
	bool leftArrowDown{ false };
	bool downArrowDown{ false };
	bool rightArrowDown{ false };
	bool spaceDown{ false };
	//Mouse
	bool mouseDown{ false };
	//Mouse specific
	bool mouse1Down{ false };
	bool mouse2Down{ false };

public:
	//Polls all events
	void PollEvents();
	//Returns true or false if quit event has been raised
	bool GetQuitState();
	//Sets the quitState variable
	void SetQuitState(bool _input) { programQuit = _input; }
	//Returns true or false if specific key has been pressed
	bool GetKeyDown(const std::string& _key);
	//Returns true or false if any key has been pressed
	bool GetKeyDown();
	//Returns true or false if specific mouse button has been pressed
	bool GetMouseDown(const std::string& _button);
	//Returns true or false if any mouse button has been pressed
	bool GetMouseDown();
};

