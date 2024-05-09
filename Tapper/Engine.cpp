#include "Engine.h"

Engine::Engine()
{
	//Initialises SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	//Sets window dimensions
	windowWidth = 964;
	windowHeight = 900;

	//Creates window and centers it
	window = SDL_CreateWindow("Tapper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "Window creation FAILED " << SDL_GetError() << std::endl;
	}

	//Creates renderer and sets it to the size of the window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << "Renderer creation FAILED " << SDL_GetError() << std::endl;
	}
	SDL_RenderSetLogicalSize(renderer, windowWidth, windowHeight);

	//Initialises TTF
	if (TTF_Init() < 0)
	{
		std::cout << "TTF creation FAILED " << TTF_GetError() << std::endl;
	}

	//Initialises Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		std::cout << "Mixer creation FAILED " << Mix_GetError() << std::endl;
	}
	else
	{
		//Adds music and sets volume
		menuMusic = Mix_LoadMUS("Data\\Menu.mp3");
		gameMusic = Mix_LoadMUS("Data\\Game.mp3");
		gameOverMusic = Mix_LoadMUS("Data\\Game Over.mp3");
		Mix_MasterVolume(60);
	}
	
	//Creates an instance of the controller
	controller = new EventController();
}

void Engine::AddLayerElement(std::shared_ptr<GameObject> _input, int _layer)
{
	//Creates an instance of the LayeredGameObject struct and assigns it to the layerElements vector
	LayeredGameObject layeredElement(_input, _layer);
	layerElements.push_back(layeredElement);
	//Sorts the layer before returning
	SortLayers();
}

//Sorting algorithm for std::sort - returns true if the lhs' layer is smaller than the rhs' layer
bool Engine::CompareLayers(const LayeredGameObject &lhs, const LayeredGameObject &rhs)
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

//Predicate for std::remove - returns true if the shared pointer is unique or if the GameObject's destroy variable is true
bool Engine::LayerPredicate(const LayeredGameObject& _input)
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
	//Sorts the layers in ascending order
	std::sort(layerElements.begin(), layerElements.end(), CompareLayers);
}

//Clears the window
void Engine::Reset()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	layerElements.erase(std::remove_if(layerElements.begin(), layerElements.end(), LayerPredicate), layerElements.end());
}

void Engine::Update()
{
	//If the exit button has been clicked, exit the program
	if (controller->GetQuitState() == true)
	{
		SetLoopState(false);
		return;
	}

	//If the layerElements vector is about to relocate, reserve it additional memory
	if (layerElements.size() >= layerElements.capacity())
	{
		layerElements.reserve(layerElements.size() + 3);
	}

	//Calls the Update() and Draw() function for each element in the layerElements vector
	for (LayeredGameObject obj : layerElements)
	{
		obj.gameObject->Update();
		obj.gameObject->Draw();
	}
}

//Draws to the window
void Engine::Present()
{
	SDL_RenderPresent(renderer);
}

void Engine::Music_PlayMenu()
{
	if (menu_IsPlaying == false)
	{
		Mix_PlayMusic(menuMusic, -1);
		menu_IsPlaying = true;
		game_IsPlaying = false;
		gameOver_IsPlaying = false;
	}
}

void Engine::Music_PlayGame()
{
	if (game_IsPlaying == false)
	{
		Mix_PlayMusic(gameMusic, -1);
		menu_IsPlaying = false;
		game_IsPlaying = true;
		gameOver_IsPlaying = false;
	}
}

void Engine::Music_PlayGameOver()
{
	if (gameOver_IsPlaying == false)
	{
		Mix_PlayMusic(gameOverMusic, -1);
		menu_IsPlaying = false;
		game_IsPlaying = false;
		gameOver_IsPlaying = true;
	}
}