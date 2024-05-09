#include "EnemyHandler.h"

//Predicate - returns true if the pointer is unique, or if the element's destroy variable is true
bool EnemyHandler::EnemyPredicate(const Enemy& _input)
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

EnemyHandler::~EnemyHandler()
{
	engine = nullptr;
}

void EnemyHandler::AddEnemy(int _y, int _layer)
{
	//Creates a new shared pointer and gives it a random spritesheet
	std::shared_ptr<Patron> newPatron = std::make_shared<Patron>(renderer, _y);
	newPatron->LoadImage("Data\\Patron" + std::to_string(1 + rand() % 5) + ".bmp");
	//Assigns the shared pointer to an enemy struct and adds it to the vector
	Enemy newEnemy(newPatron);
	enemyVector.push_back(newEnemy);
	//Adds the object to the engine
	engine->AddLayerElement(newEnemy.gameObject, _layer);
}

void EnemyHandler::Update()
{
	//Erases any elements according to the predicate
	enemyVector.erase(std::remove_if(enemyVector.begin(), enemyVector.end(), EnemyPredicate), enemyVector.end());
	//Reserves additional space in memory if vector relocation will happen
	if (enemyVector.size() >= enemyVector.capacity())
	{
		enemyVector.reserve(enemyVector.size() + 3);
	}
}
