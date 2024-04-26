#pragma once
#include <SDL.h>
#include "GameObject.h"
#include "EventController.h"
#include <iostream>
#include <vector>
#include <algorithm>

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
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };

	int windowWidth{ 0 };
	int windowHeight{ 0 };

	EventController* controller{ nullptr };

	std::vector<LayeredGameObject> layerElements;
	bool sortLayers{ false };

	//Custom sorting function for std::sort
	static bool compareLayers(const LayeredGameObject &lhs, const LayeredGameObject &rhs);
	//Custom predicate for std::remove_if
	static bool layerPredicate(const LayeredGameObject& _input);

	bool gameLoop{ false };
public:
	Engine();
	//~Engine();

	//Returns the renderer
	SDL_Renderer* GetRenderer();
	
	//Returns the controller
	EventController* GetController();
	//Calls poll event in controller
	void ControllerPollEvents();
	
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

	//Gets current game state
	bool GetLoopState();
	//Sets current game state
	void SetLoopState(bool _state);
};