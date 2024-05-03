#pragma once
#include "GameObject.h"
#include "Engine.h"
#include "Glass.h"

struct Projectile
{
	Projectile(std::shared_ptr<Glass> _input)
	{
		gameObject = _input;
	};
	std::shared_ptr<Glass> gameObject;
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

	int GetVectorSize() { return projectileVector.size(); }

	SDL_Rect GetIndexedRect(int _index) { return projectileVector[_index].gameObject->GetRect(); }

	bool GetIndexedMoveLeft(int _index) { return projectileVector[_index].gameObject->GetMoveLeft(); }
	bool GetIndexedGlassEnd(int _index) { return projectileVector[_index].gameObject->GetGlassEnd(); }

	void SetIndexedDestroy(int _index, bool _destroy) { projectileVector[_index].gameObject->SetDestroy(_destroy); }

	void ClearVector();

	void Update();
	void Draw() {}
};