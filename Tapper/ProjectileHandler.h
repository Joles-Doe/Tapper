#pragma once
#include "GameObject.h"
#include "Engine.h"
#include "Glass.h"

struct Projectile
{
	Projectile(std::shared_ptr<GameObject> _input)
	{
		gameObject = _input;
	};
	std::shared_ptr<GameObject> gameObject;
};

class ProjectileHandler : public GameObject
{
private:
	Engine* engine{ nullptr };

	std::vector<Projectile> projectileVector;
	static bool ProjectilePredicate(const Projectile& _input);
public:
	ProjectileHandler(SDL_Renderer* _rend, Engine* _engine) : GameObject(_rend) { engine = _engine; }

	void AddProjectile(int _X, int _Y, std::string _direction, int _layer);

	void Update();
	void Draw() {}
};

