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
void Instructions(Engine& sdlEngine, const float frameDelay);
int Game(Engine& sdlEngine, const float frameDelay);
void GameOver(Engine& sdlEngine, const float frameDelay, int _round);

int main(int argc, char* argv[])
{
	//Sets seed for rand()
	srand(time(0));
	
	//Variables relating to the frame delay
	const int FPS{ 60 };
	const float frameDelay{ 1000 / FPS };

	//Engine instance
	Engine sdlEngine = Engine();

	bool menuReturn{ false };
	int rounds{ 0 };
	while (true)
	{
		//Call the menu function
		menuReturn = Menu(sdlEngine, frameDelay);
		//If the quit button has been clicked, or the return button in the menu has been clicked
		if (sdlEngine.GetController()->GetQuitState() == true || menuReturn == true)
		{
			//End the program
			break;
		}
		else
		{
			//Show instructions
			Instructions(sdlEngine, frameDelay);
			//Begin the game
			rounds = Game(sdlEngine, frameDelay);
			//Once the game has finished, show the game over screen
			GameOver(sdlEngine, frameDelay, rounds);
		}
	}

	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
	return 0;
}

bool Menu(Engine& sdlEngine, const float frameDelay)
{
	//Music
	sdlEngine.Music_PlayMenu();

	//Text elements
	//Title
	std::shared_ptr<Text> titleText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 200);
	titleText->ChangeColor(255, 255, 255);
	titleText->ChangeText("TAPPER");
	titleText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (titleText->GetRect().w / 2), 50);
	sdlEngine.AddLayerElement(titleText, 0);

	//Start button
	std::shared_ptr<Text> startText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 100);
	startText->ChangeColor(255, 255, 255);
	startText->ChangeText("START");
	startText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (startText->GetRect().w / 2), sdlEngine.GetWindowHeight() / 2);
	sdlEngine.AddLayerElement(startText, 0);

	//Exit button
	std::shared_ptr<Text> exitText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 80);
	exitText->ChangeColor(255, 255, 255);
	exitText->ChangeText("EXIT");
	exitText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (exitText->GetRect().w / 2), (sdlEngine.GetWindowHeight() / 2 - exitText->GetRect().h / 2) + startText->GetRect().h + 80);
	sdlEngine.AddLayerElement(exitText, 0);

	//Variables related to frame delay
	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };

	bool exitButtonClicked{ false };

	//Rect instances created to record the position of the mouse and the start button
	SDL_Rect startTextRect = startText->GetRect();
	SDL_Rect exitTextRect = exitText->GetRect();
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

		//If the user either left or right clicks
		if (sdlEngine.GetController()->GetMouseDown("l") == true || sdlEngine.GetController()->GetMouseDown("r") == true)
		{
			//Set the mouse rect position to the mouse
			SDL_GetMouseState(&mouseRect.x, &mouseRect.y);
			//Check if the mouse clicked on the start button
			if (SDL_HasIntersection(&startTextRect, &mouseRect))
			{
				sdlEngine.SetLoopState(false);
			}
			//Check if the mouse clicked on the exit button
			if (SDL_HasIntersection(&exitTextRect, &mouseRect))
			{
				exitButtonClicked = true;
				sdlEngine.SetLoopState(false);
			}
		}

		sdlEngine.Present();
		
		//Delay the program to keep 60 FPS
		frameEnd = SDL_GetTicks();
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	//Once the menu loop ends, remove everything from the heap
	titleText.reset();
	startText.reset();
	exitText.reset();
	sdlEngine.Reset();

	return exitButtonClicked;
}

void Instructions(Engine& sdlEngine, const float frameDelay)
{
	//Instructions
	std::shared_ptr<Background> instructions = std::make_shared<Background>(sdlEngine.GetRenderer());
	instructions->LoadImage("Data\\Instructions.bmp");
	sdlEngine.AddLayerElement(instructions, 0);

	//Variables related to frame delay
	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };

	sdlEngine.SetLoopState(true);
	while (sdlEngine.GetLoopState())
	{
		frameStart = SDL_GetTicks();

		sdlEngine.Reset();
		sdlEngine.ControllerPollEvents();
		sdlEngine.Update();

		if (sdlEngine.GetController()->GetKeyDown("spacebar"))
		{
			sdlEngine.SetLoopState(false);
		}

		sdlEngine.Present();

		//Delay the program to keep 60 FPS
		frameEnd = SDL_GetTicks();
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	//Once the instruction loop ends, remove everything from the heap
	instructions.reset();
	sdlEngine.Reset();
}

int Game(Engine& sdlEngine, const float frameDelay)
{
	//Music
	sdlEngine.Music_PlayGame();

	//Background elements
	//Floor
	std::shared_ptr<Background> floor = std::make_shared<Background>(sdlEngine.GetRenderer());
	floor->LoadImage("Data\\Floor.bmp");
	sdlEngine.AddLayerElement(floor, 1);
	//Backwall
	std::shared_ptr<Background> backWall = std::make_shared<Background>(sdlEngine.GetRenderer());
	backWall->LoadImage("Data\\Back Wall.bmp");
	sdlEngine.AddLayerElement(backWall, 2);
	//Bar counters
	std::shared_ptr<Background> barCounters = std::make_shared<Background>(sdlEngine.GetRenderer());
	barCounters->LoadImage("Data\\Counters.bmp");
	sdlEngine.AddLayerElement(barCounters, 4);
	//Side walls
	std::shared_ptr<Background> sideWall = std::make_shared<Background>(sdlEngine.GetRenderer());
	sideWall->LoadImage("Data\\Side Wall.bmp");
	sdlEngine.AddLayerElement(sideWall, 6);

	//Player
	std::shared_ptr<Player> player = std::make_shared<Player>(sdlEngine.GetRenderer(), sdlEngine.GetController());
	player->LoadImage("Data\\Barman.bmp");
	sdlEngine.AddLayerElement(player, 5);

	//Projecitle handler
	std::shared_ptr<ProjectileHandler> projectileHandler = std::make_shared<ProjectileHandler>(sdlEngine.GetRenderer(), &sdlEngine);
	sdlEngine.AddLayerElement(projectileHandler, 0);
	//Enemy handler
	std::shared_ptr<EnemyHandler> enemyHandler = std::make_shared<EnemyHandler>(sdlEngine.GetRenderer(), &sdlEngine);
	sdlEngine.AddLayerElement(enemyHandler, 0);

	//Text elements
	//Lives text
	std::shared_ptr<Text> livesText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 60);
	livesText->ChangeText("Lives: 3");
	livesText->SetRectPos(30, 30);
	sdlEngine.AddLayerElement(livesText, 8);
	//Round text
	std::shared_ptr<Text> roundText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 80);
	roundText->ChangeText("Round " + std::to_string(1));
	roundText->SetRectPos(sdlEngine.GetWindowWidth() / 2 - roundText->GetRect().w / 2, sdlEngine.GetWindowHeight() / 2 - roundText->GetRect().h);
	sdlEngine.AddLayerElement(roundText, 8);
	//Round text 2
	std::shared_ptr<Text> roundText_2 = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 80);
	roundText_2->ChangeText("Press any key to start");
	roundText_2->SetRectPos(sdlEngine.GetWindowWidth() / 2 - roundText_2->GetRect().w / 2, (sdlEngine.GetWindowHeight() / 2 - roundText_2->GetRect().h) + roundText->GetRect().h);
	sdlEngine.AddLayerElement(roundText_2, 8);

	//Variables relating to collision
	SDL_Rect collisionA{ 0 };
	SDL_Rect collisionB{ 0 };
	SDL_Rect playerRect{ 0 };

	//Variables relating to frame delay
	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };

	//Variables relating to player lives and rounds
	int lives{ 3 };
	bool startNewRound{ true };
	bool addRound{ false };
	bool showText{ true };
	bool lostLife{ false };
	int round{ 0 };
	Uint64 roundTimer{ 0 };

	//Variables relating to the spawning of enemies
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

		//If a new round should be started
		if (startNewRound == true)
		{
			//If the player succeeded the previous round, increase the round counter (will only run once until the start of the next round)
			if (addRound == true)
			{
				addRound = false;
				round += 1;
			}
			//If a life has been lost, reduce the life counter and change the life text (will only run once until the start of the next round)
			if (lostLife == true)
			{
				lostLife = false;
				livesText->ChangeText("Lives: " + std::to_string(lives));
				livesText->SetRectPos(30, 30);
			}
			//Make the round text visible, and clear the enemy and projectile vectors (will only run once until the start of the next round)
			if (showText == true)
			{
				showText = false;
				roundText->ChangeText("Round " + std::to_string(round + 1));
				roundText->SetRectPos(sdlEngine.GetWindowWidth() / 2 - roundText->GetRect().w / 2, sdlEngine.GetWindowHeight() / 2 - roundText->GetRect().h);
				roundText_2->SetRectPos(sdlEngine.GetWindowWidth() / 2 - roundText_2->GetRect().w / 2, (sdlEngine.GetWindowHeight() / 2 - roundText_2->GetRect().h) + roundText->GetRect().h);
				roundText->SetVisible(true);
				roundText_2->SetVisible(true);
				projectileHandler->ClearVector();
				enemyHandler->ClearVector();
			}
			//After a second, check if the player presses a key
			if (sdlEngine.GetController()->GetKeyDown() && SDL_GetTicks() >= roundTimer + 1000)
			{
				//Allow the player to act
				player->SetAct(true);
				//Make the round text disappear
				roundText->SetVisible(false);
				roundText_2->SetVisible(false);
				//Set showtext back to true, so that it runs once a new round starts
				showText = true;
				//Set new round to false
				startNewRound = false;
				//Begin to spawn enemies - calculate how many enemies spawn this round
				spawnEnemies = false;
				spawnNew = true;
				enemyCount = 0;
				maxEnemies = (3 * round) + 3;
				roundTimer = SDL_GetTicks();
			}
		}
		else
		{
			//If spawn enemies is false
			if (spawnEnemies == false)
			{
				//Check if a second and a half has gone by
				if (SDL_GetTicks() > roundTimer + 1500)
				{
					//Start spawning enemies
					spawnEnemies = true;
				}
			}
			else
			{
				//If the amount of enemies hasn't exceeded the max enemies
				if (enemyCount < maxEnemies)
				{
					//If a new enemy needs to be spawned
					if (spawnNew == true)
					{
						//Set spawnNew back to false and increase the enemy count
						spawnNew = false;
						enemyCount++;
						//Reset the timer and set a random spawn delay
						roundTimer = SDL_GetTicks();
						spawnDelay = 1000 + rand() % 5000;
						//Spawn an enemy
						enemyHandler->AddEnemy(rand() % 3, 3);
					}
					//If the spawnDelay has been exceeded
					else if (SDL_GetTicks() > roundTimer + spawnDelay)
					{
						spawnNew = true;
					}
				}
				else
				{
					//If all enemies have been dealt with
					if (enemyHandler->GetVectorSize() == 0)
					{
						//Start a new round, and reset the timer
						startNewRound = true;
						addRound = true;
						roundTimer = SDL_GetTicks();
						//Stop the player from acting
						player->SetAct(false);
					}
				}
			}
			//Checks if any glasses have reached either end of the counter
			for (int x = 0; x < projectileHandler->GetVectorSize(); x++)
			{
				if (projectileHandler->GetIndexedGlassEnd(x) == true)
				{
					//Restart the round and reduce a life, reset the timer
					startNewRound = true;
					lostLife = true;
					lives--;
					roundTimer = SDL_GetTicks();
					//Stop the player from acting
					player->SetAct(false);
					break;
				}
			}
			//Checks if any enemies have reached the end of the bar
			for (int x = 0; x < enemyHandler->GetVectorSize(); x++)
			{
				if (enemyHandler->GetIndexedReachedEnd(x) == true)
				{
					//Restart the round and reduce a life, reset the timer
					startNewRound = true;
					lostLife = true;
					lives--;
					roundTimer = SDL_GetTicks();
					//Stop the player from acting
					player->SetAct(false);
					break;
				}
			}
			//If all lives have been depleted, set the game loop to false
			if (lives == 0)
			{
				sdlEngine.SetLoopState(false);
			}
			//Check if a new glass needs to be spawned (moving left to enemies)
			if (player->CheckNewGlass() == true)
			{
				projectileHandler->AddProjectile(player->GetRectX(), player->GetYIndex(), "l", 5, true);
			}

			//Check if a new glass needs to be spawned (moving right to barman)
			for (int x = 0; x < enemyHandler->GetVectorSize(); x++)
			{
				if (enemyHandler->GetIndexedReturn(x) == true)
				{
					projectileHandler->AddProjectile(enemyHandler->GetIndexedRect(x).x, enemyHandler->GetIndexedYIndex(x), "r", 5, false);
					enemyHandler->SetIndexedReturn(x, false);
				}
			}

			//Collision
			for (int x = 0; x < projectileHandler->GetVectorSize(); x++)
			{
				//Set collisionA to the current glass in the loop
				collisionA = projectileHandler->GetIndexedRect(x);
				for (int y = 0; y < enemyHandler->GetVectorSize(); y++)
				{
					//Set collisionB to the current enemy in the loop
					collisionB = enemyHandler->GetIndexedRect(y);
					//If both rects have collided
					if (SDL_HasIntersection(&collisionA, &collisionB))
					{
						//Check if the enemy is not leaving and the glass is moving left
						if (enemyHandler->GetIndexedLeave(y) == false && projectileHandler->GetIndexedMoveLeft(x) == true)
						{
							//Destroy the glass and set the enemy's action to leaving
							projectileHandler->SetIndexedDestroy(x, true);
							enemyHandler->SetIndexedLeave(y, true);
						}
					}
				}
				//Set playerRect to the player's current position
				playerRect = player->GetRect();
				//If the current glass and the player have collided
				if (SDL_HasIntersection(&collisionA, &playerRect))
				{
					//Check if the glass is moving right
					if (projectileHandler->GetIndexedMoveLeft(x) == false)
					{
						//Destroy the glass
						projectileHandler->SetIndexedDestroy(x, true);
					}
				}
			}
		}
		sdlEngine.Present();
		//Delay the program to keep 60FPS
		frameEnd = SDL_GetTicks();
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	//Once the loop has ended, remove everything from the heap
	floor.reset();
	backWall.reset();
	barCounters.reset();
	sideWall.reset();
	player.reset();
	projectileHandler.reset();
	enemyHandler.reset();
	livesText.reset();
	roundText.reset();
	roundText_2.reset();
	sdlEngine.Reset();

	return (round + 1);
}

void GameOver(Engine& sdlEngine, const float frameDelay, int _round)
{
	//Music
	sdlEngine.Music_PlayGameOver();

	//Text elements
	//Title
	std::shared_ptr<Text> titleText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 200);
	titleText->ChangeColor(255, 255, 255);
	titleText->ChangeText("GAME OVER!");
	titleText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (titleText->GetRect().w / 2), 50);
	sdlEngine.AddLayerElement(titleText, 0);

	//Round text
	std::shared_ptr<Text> roundText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 100);
	roundText->ChangeColor(255, 255, 255);
	roundText->ChangeText("You got to Round " + std::to_string(_round));
	roundText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (roundText->GetRect().w / 2), sdlEngine.GetWindowHeight() / 2 - 100);
	sdlEngine.AddLayerElement(roundText, 0);

	//Return button
	std::shared_ptr<Text> returnText = std::make_shared<Text>(sdlEngine.GetRenderer(), "Data\\munro.ttf", 80);
	returnText->ChangeColor(255, 255, 255);
	returnText->ChangeText("RETURN");
	returnText->SetRectPos((sdlEngine.GetWindowWidth() / 2) - (returnText->GetRect().w / 2), (sdlEngine.GetWindowHeight() / 2 - returnText->GetRect().h / 2) + roundText->GetRect().h + 200);
	sdlEngine.AddLayerElement(returnText, 0);

	//Variables related to frame delay
	Uint64 frameStart{ 0 };
	Uint64 frameEnd{ 0 };

	bool exitButtonClicked{ false };

	//Rect instances created to record the position of the mouse and the start button
	SDL_Rect returnTextRect = returnText->GetRect();
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

		//If the user either left or right clicks
		if (sdlEngine.GetController()->GetMouseDown("l") == true || sdlEngine.GetController()->GetMouseDown("r") == true)
		{
			//Set the mouse rect position to the mouse
			SDL_GetMouseState(&mouseRect.x, &mouseRect.y);
			//Check if the mouse clicked on the return button
			if (SDL_HasIntersection(&returnTextRect, &mouseRect))
			{
				sdlEngine.SetLoopState(false);
			}
		}

		sdlEngine.Present();

		//Delay the program to keep 60 FPS
		frameEnd = SDL_GetTicks();
		if (frameDelay > frameEnd - frameStart)
		{
			SDL_Delay(frameDelay - (frameEnd - frameStart));
		}
	}

	//Once the loop ends, remove everything from the heap
	titleText.reset();
	roundText.reset();
	returnText.reset();
	sdlEngine.Reset();
}