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
}

//Engine::~Engine()
//{
//}

void Engine::AddLayerElement(std::shared_ptr<GameObject> _input, int _layer)
{
	sortLayers = true;
	LayeredGameObject layeredElement(_input, _layer);
	layerElements.push_back(layeredElement);
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

void Engine::SortLayers()
{
	std::sort(layerElements.begin(), layerElements.end(), compareLayers);
	sortLayers = false;
}

//clears the renderer
void Engine::Reset()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Engine::Update(SDL_Event e)
{
	//Update for loop
	for (LayeredGameObject obj : layerElements)
	{
		obj.gameObject->Update(e);
	}
}

//draws the renderer to the window
void Engine::Present()
{
	SDL_RenderPresent(renderer);
}

//returns renderer
SDL_Renderer* Engine::GetRenderer()
{
	//std::cout << renderer;
	return renderer;
}