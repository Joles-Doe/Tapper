#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "GameObject.h"
#include "EventController.h"
#include <iostream>
#include <vector>
#include <algorithm>

//Custom struct containing an instance of the GameObject class and it's layer
struct LayeredGameObject
{
	LayeredGameObject(std::shared_ptr<GameObject> _input, int _layer)
	{
		gameObject = _input;
		layer = _layer;
	};
	std::shared_ptr<GameObject> gameObject;
	int layer;
};

class Engine
{
private:
	//Window and Renderer pointers
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	//Variables containing the dimensions of the window
	int windowWidth{ 0 };
	int windowHeight{ 0 };

	//Controller pointer
	EventController* controller{ nullptr };

	//Music pointers
	Mix_Music* menuMusic{ nullptr };
	Mix_Music* gameMusic{ nullptr };
	Mix_Music* gameOverMusic{ nullptr };
	//Variables containing music information
	bool menu_IsPlaying{ false };
	bool game_IsPlaying{ false };
	bool gameOver_IsPlaying{ false };

	//Vector containing layerElements
	std::vector<LayeredGameObject> layerElements;
	int vecSize{ 0 };

	//Custom sorting function for std::sort
	static bool CompareLayers(const LayeredGameObject &lhs, const LayeredGameObject &rhs);
	//Custom predicate for std::remove_if
	static bool LayerPredicate(const LayeredGameObject& _input);

	//GameLoop variable - program will exit if this is set to false
	bool gameLoop{ false };
public:
	Engine();

	//Returns the renderer
	SDL_Renderer* GetRenderer() { return renderer; }
	
	//Returns the controller
	EventController* GetController() { return controller; }
	//Calls poll event in controller
	void ControllerPollEvents() { controller->PollEvents(); }
	
	//Adds an element to the engine
	void AddLayerElement(std::shared_ptr<GameObject> _input, int _layer);
	//Sorts layers in ascending order
	void SortLayers();
	//Clears the renderer
	void Reset();
	//Updates attached objects
	void Update();
	//Draws the renderer to the window
	void Present();

	//Getters and Setters for the loop state variable
	bool GetLoopState() { return gameLoop; }
	void SetLoopState(bool _state) { gameLoop = _state; }

	//Plays the background music, if not already playing
	void Music_PlayMenu();

	//Plays the background music, if not already playing
	void Music_PlayGame();

	//Plays the game over music, if not already playing
	void Music_PlayGameOver();

	//Returns the width of the window
	int GetWindowWidth() { return windowWidth; }
	//Returns the height of the window
	int GetWindowHeight() { return windowHeight; }
};