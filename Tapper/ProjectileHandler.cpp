#include "ProjectileHandler.h"

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
	std::shared_ptr<Glass> newGlass = std::make_shared<Glass>(renderer, _x, _y, _direction);
	newGlass->LoadImage("GlassPlaceholder.bmp");

	Projectile newProjectile(newGlass);
	projectileVector.push_back(newProjectile);

	engine->AddLayerElement(newProjectile.gameObject, _layer);
	return;
}

void ProjectileHandler::ClearVector()
{
	projectileVector.clear();
}

void ProjectileHandler::Update()
{
	projectileVector.erase(std::remove_if(projectileVector.begin(), projectileVector.end(), ProjectilePredicate), projectileVector.end());

	if (projectileVector.size() >= projectileVector.capacity())
	{
		projectileVector.reserve(projectileVector.size() + 3);
	}
}
