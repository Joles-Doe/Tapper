#include "EnemyHandler.h"

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

void EnemyHandler::AddEnemy(int _y, int _layer)
{
	std::shared_ptr<Patron> newPatron = std::make_shared<Patron>(renderer, _y);
	newPatron->LoadImage("Patron" + std::to_string(1 + rand() % 5) + ".bmp");

	Enemy newEnemy(newPatron);
	enemyVector.push_back(newEnemy);

	engine->AddLayerElement(newEnemy.gameObject, _layer);
	return;
}

void EnemyHandler::Update()
{
	enemyVector.erase(std::remove_if(enemyVector.begin(), enemyVector.end(), EnemyPredicate), enemyVector.end());

	if (enemyVector.size() >= enemyVector.capacity())
	{
		enemyVector.reserve(enemyVector.size() + 3);
	}
}
