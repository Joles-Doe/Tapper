#include "Engine.h"


//default constructor
Engine::Engine()
{
	//initialises SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//sets window dimensions
	windowWidth = 964;
	windowHeight = 900;

	//creates window and centers it
	window = SDL_CreateWindow("Tapper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "Window creation FAILED " << SDL_GetError() << std::endl;
	}

	//creates window and sets it to the size of the window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Renderer creation FAILED " << SDL_GetError() << std::endl;
	}
	SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);

	controller = new EventController();
}

//Engine::~Engine()
//{
//}

void Engine::AddLayerElement(std::shared_ptr<GameObject> _input, int _layer)
{
	sortLayers = true;
	LayeredGameObject layeredElement(_input, _layer);
	layerElements.push_back(layeredElement);
	std::cout << "Added to layer" << std::endl;
	return;
}

bool Engine::compareLayers(const LayeredGameObject &lhs, const LayeredGameObject &rhs)
{
	if (lhs.layer == rhs.layer)
	{
		return false;
	}
	else
	{
		return lhs.layer < rhs.layer;
	}
}

bool Engine::layerPredicate(const LayeredGameObject& _input)
{
	if (_input.gameObject.unique())
	{
		return _input.gameObject.unique();
	}
	else if (_input.gameObject->GetDestroy())
	{
		return _input.gameObject->GetDestroy();
	}
	else
	{
		return false;
	}
}

void Engine::SortLayers()
{
	std::sort(layerElements.begin(), layerElements.end(), compareLayers);
	sortLayers = false;
	return;
}

//clears the renderer
void Engine::Reset()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//vec.erase(std::remove_if(vec.begin(), vec.end(), predicate), vec.end());
	layerElements.erase(std::remove_if(layerElements.begin(), layerElements.end(), layerPredicate), layerElements.end());

	return;
}

void Engine::Update()
{
	if (controller->GetQuitState() == true)
	{
		SetLoopState(false);
		return;
	}


	if (layerElements.size() >= layerElements.capacity())
	{
		layerElements.reserve(layerElements.size() + 3);
	}

	//Update for loop
	for (LayeredGameObject obj : layerElements)
	{
		obj.gameObject->Update();
		obj.gameObject->Draw();
	}

	return;
}

//draws the renderer to the window
void Engine::Present()
{
	SDL_RenderPresent(renderer);
	return;
}

bool Engine::GetLoopState()
{
	return gameLoop;
}

void Engine::SetLoopState(bool _state)
{
	gameLoop = _state;
	return;
}

//returns renderer
SDL_Renderer* Engine::GetRenderer()
{
	//std::cout << renderer;
	return renderer;
}

EventController* Engine::GetController()
{
	return controller;
}

void Engine::ControllerPollEvents()
{
	controller->PollEvents();
}
