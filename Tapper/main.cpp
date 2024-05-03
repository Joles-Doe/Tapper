#include <SDL.h>
#include "Engine.h"
#include "GameObject.h"
#include "Background.h"
#include "Text.h"
#include "Player.h"
#include "ProjectileHandler.h"
#include "EnemyHandler.h"
#include <iostream>
#include <string>

bool Menu(Engine& sdlEngine, const float frameDelay);
void Game(Engine& sdlEngine, const float frameDelay);
Uint64 TimerStart();

int main(int argc, char* argv[])
{
	srand(time(0));
	
	const int FPS{ 60 };
	const float frameDelay{ 1000 / FPS };

	Engine sdlEngine = Engine();

	bool menuReturn{ false };
	while (true)
	{
		menuReturn = Menu(sdlEngine, frameDelay);
		Game(sdlEngine, frameDelay);

		if (sdlEngine.GetController()->GetQuitState() == true || menuReturn == true)
		{
			break;
		}
	}

	return 0;
}

bool Menu(Engine& sdlEngine, const float frameDelay)
{
	std::shared_ptr<Text> titleText = std::make_shared<Text>(sdlEngine.GetRenderer(), "munro.ttf", 200);
	titleText->ChangeColor(255, 255, 255);
	titleText->ChangeText("TAPPER");
	titleText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (titleText->GetRect().w / 2), 50);
	sdlEngine.AddLayerElement(titleText, 0);

	std::shared_ptr<Text> startText = std::make_shared<Text>(sdlEngine.GetRenderer(), "munro.ttf", 100);
	startText->ChangeColor(255, 255, 255);
	startText->ChangeText("START");
	startText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (startText->GetRect().w / 2), sdlEngine.GetWindowHeight() / 2);
	sdlEngine.AddLayerElement(startText, 0);

	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };

	bool startButtonClicked{ false };

	SDL_Rect startTextRect = startText->GetRect();
	SDL_Rect mouseRect{ 0 };
	mouseRect.w = 1;
	mouseRect.h = 1;

	sdlEngine.SetLoopState(true);
	while (sdlEngine.GetLoopState())
	{
		frameStart = SDL_GetTicks();

		sdlEngine.Reset();
		sdlEngine.ControllerPollEvents();
		sdlEngine.Update();

		if (sdlEngine.GetController()->GetMouseDown("l") == true || sdlEngine.GetController()->GetMouseDown("r") == true)
		{
			SDL_GetMouseState(&mouseRect.x, &mouseRect.y);
			startButtonClicked = SDL_HasIntersection(&startTextRect, &mouseRect);
			if (startButtonClicked == true)
			{
				sdlEngine.SetLoopState(false);
			}
		}

		sdlEngine.Present();
		
		frameEnd = SDL_GetTicks();
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	titleText.reset();
	startText.reset();

	sdlEngine.Reset();

	return startButtonClicked;
}

void Game(Engine& sdlEngine, const float frameDelay)
{
	//Creation of background objects
	std::shared_ptr<Background> floor = std::make_shared<Background>(sdlEngine.GetRenderer());
	floor->LoadImage("Floor.bmp");
	sdlEngine.AddLayerElement(floor, 1);

	std::shared_ptr<Background> backWall = std::make_shared<Background>(sdlEngine.GetRenderer());
	backWall->LoadImage("Back Wall.bmp");
	sdlEngine.AddLayerElement(backWall, 2);

	std::shared_ptr<Background> barCounters = std::make_shared<Background>(sdlEngine.GetRenderer());
	barCounters->LoadImage("Counters.bmp");
	sdlEngine.AddLayerElement(barCounters, 4);

	std::shared_ptr<Background> sideWall = std::make_shared<Background>(sdlEngine.GetRenderer());
	sideWall->LoadImage("Side Wall.bmp");
	sdlEngine.AddLayerElement(sideWall, 6);

	//Creation of the player
	std::shared_ptr<Player> player = std::make_shared<Player>(sdlEngine.GetRenderer(), sdlEngine.GetController());
	player->LoadImage("PlayerPlaceholder.bmp");
	sdlEngine.AddLayerElement(player, 5);

	//Creation of the projectile and enemy handlers
	std::shared_ptr<ProjectileHandler> projectileHandler = std::make_shared<ProjectileHandler>(sdlEngine.GetRenderer(), &sdlEngine);
	sdlEngine.AddLayerElement(projectileHandler, 0);

	std::shared_ptr<EnemyHandler> enemyHandler = std::make_shared<EnemyHandler>(sdlEngine.GetRenderer(), &sdlEngine);
	sdlEngine.AddLayerElement(enemyHandler, 0);

	//Creation of text
	std::shared_ptr<Text> livesText = std::make_shared<Text>(sdlEngine.GetRenderer(), "munro.ttf", 60);
	livesText->ChangeText("Lives: 3");
	livesText->SetRectPos(30, 30);
	sdlEngine.AddLayerElement(livesText, 8);

	SDL_Rect collisionA{ 0 };
	SDL_Rect collisionB{ 0 };
	SDL_Rect playerRect{ 0 };

	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };

	int lives{ 3 };
	bool startNewRound{ true };
	bool lostLife{ false };
	int round{ 0 };
	Uint64 roundTimer{ 0 };

	bool spawnEnemies{ false };
	bool spawnNew{ true };
	int spawnDelay{ 0 };
	int enemyCount{ 0 };
	int maxEnemies{ 0 };

	sdlEngine.SetLoopState(true);
	while (sdlEngine.GetLoopState())
	{
		frameStart = SDL_GetTicks();

		sdlEngine.Reset();
		sdlEngine.ControllerPollEvents();
		sdlEngine.Update();

		if (startNewRound == true)
		{
			if (lostLife == true)
			{
				livesText->ChangeText("Lives: " + std::to_string(lives) );
				livesText->SetRectPos(30, 30);
			}
			else
			{
				round++;
			}
			startNewRound = false;
			spawnEnemies = false;
			spawnNew = true;
			enemyCount = 0;
			maxEnemies = (3 * round) + 3;
			projectileHandler->ClearVector();
			enemyHandler->ClearVector();
			roundTimer = TimerStart();
		}
		else
		{
			if (spawnEnemies == false)
			{
				if (SDL_GetTicks() > roundTimer + 1500)
				{
					spawnEnemies = true;
				}
			}
			else
			{
				if (enemyCount < maxEnemies)
				{
					if (spawnNew == true)
					{
						spawnNew = false;
						enemyCount++;
						roundTimer = TimerStart();
						spawnDelay = 1000 + rand() % 5000;
						enemyHandler->AddEnemy(rand() % 3, 3);
					}
					else if (SDL_GetTicks() > roundTimer + spawnDelay)
					{
						spawnNew = true;
					}
				}
				else
				{
					if (enemyHandler->GetVectorSize() == 0)
					{
						startNewRound = true;
					}
				}
			}

			for (int x = 0; x < projectileHandler->GetVectorSize(); x++)
			{
				if (projectileHandler->GetIndexedGlassEnd(x) == true)
				{
					startNewRound = true;
					lostLife = true;
					lives--;
					break;
				}
			}
			for (int x = 0; x < enemyHandler->GetVectorSize(); x++)
			{
				if (enemyHandler->GetIndexedReachedEnd(x) == true)
				{
					startNewRound = true;
					lostLife = true;
					lives--;
					break;
				}
			}
			if (lives == 0)
			{
				sdlEngine.SetLoopState(false);
			}
		}

		if (player->CheckNewGlass() == true)
		{
			projectileHandler->AddProjectile(player->GetRectX(), player->GetYIndex(), "l", 5);
		}

		for (int x = 0; x < enemyHandler->GetVectorSize(); x++)
		{
			if (enemyHandler->GetIndexedReturn(x) == true)
			{
				projectileHandler->AddProjectile(enemyHandler->GetIndexedRect(x).x, enemyHandler->GetIndexedYIndex(x), "r", 5);
				enemyHandler->SetIndexedReturn(x, false);
			}
		}

		for (int x = 0; x < projectileHandler->GetVectorSize(); x++)
		{
			collisionA = projectileHandler->GetIndexedRect(x);
			for (int y = 0; y < enemyHandler->GetVectorSize(); y++)
			{
				collisionB = enemyHandler->GetIndexedRect(y);
				if (SDL_HasIntersection(&collisionA, &collisionB))
				{
					if (enemyHandler->GetIndexedLeave(y) == false && projectileHandler->GetIndexedMoveLeft(x) == true)
					{
						projectileHandler->SetIndexedDestroy(x, true);
						enemyHandler->SetIndexedLeave(y, true);
					}
				}
			}
			playerRect = player->GetRect();
			if (SDL_HasIntersection(&collisionA, &playerRect))
			{
				if (projectileHandler->GetIndexedMoveLeft(x) == false)
				{
					projectileHandler->SetIndexedDestroy(x, true);
				}
			}
		}

		sdlEngine.Present();

		frameEnd = SDL_GetTicks();
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	floor.reset();
	backWall.reset();
	barCounters.reset();
	sideWall.reset();
	player.reset();
	projectileHandler.reset();
	enemyHandler.reset();
	
	livesText.reset();

	sdlEngine.Reset();
}

Uint64 TimerStart()
{
	return SDL_GetTicks();
}