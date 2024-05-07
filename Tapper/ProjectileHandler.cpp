#include "ProjectileHandler.h"

//Predicate - returns true if the GameObject instance is unique or the destroy variable is true
bool ProjectileHandler::ProjectilePredicate(const Projectile& _input)
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

void ProjectileHandler::AddProjectile(int _x, int _y, std::string _direction, int _layer)
{
	//Creates a new shared pointer and gives it a sprite
	std::shared_ptr<Glass> newGlass = std::make_shared<Glass>(renderer, _x, _y, _direction);
	newGlass->LoadImage("GlassPlaceholder.bmp");
	//Assigns the shared pointer to projectile struct and adds it to the vector
	Projectile newProjectile(newGlass);
	projectileVector.push_back(newProjectile);
	//Adds the object to the engine
	engine->AddLayerElement(newProjectile.gameObject, _layer);
}

void ProjectileHandler::ClearVector()
{
	projectileVector.clear();
}

void ProjectileHandler::Update()
{
	//Erases any elements according to the predicate
	projectileVector.erase(std::remove_if(projectileVector.begin(), projectileVector.end(), ProjectilePredicate), projectileVector.end());
	//Reserves additional space in memory if vector relocation will happen
	if (projectileVector.size() >= projectileVector.capacity())
	{
		projectileVector.reserve(projectileVector.size() + 3);
	}
}
