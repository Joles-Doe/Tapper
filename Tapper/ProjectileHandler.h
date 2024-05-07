#pragma once
#include "GameObject.h"
#include "Engine.h"
#include "Glass.h"

//Custom struct used for the predicate
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
	//Engine
	Engine* engine{ nullptr };

	//Vector containing all of the glasses
	std::vector<Projectile> projectileVector;
	//Predicate for the projectiles
	static bool ProjectilePredicate(const Projectile& _input);
public:
	ProjectileHandler(SDL_Renderer* _rend, Engine* _engine) : GameObject(_rend) { engine = _engine; }

	//Adds a projectile to the vector and adds it to the engine
	void AddProjectile(int _X, int _Y, std::string _direction, int _layer);

	//Returns the size of the projectile vector
	int GetVectorSize() { return projectileVector.size(); }

	//Returns a rect from an element of the enemy vector according to an index
	SDL_Rect GetIndexedRect(int _index) { return projectileVector[_index].gameObject->GetRect(); }
	//Returns the moveLeft variable from an element of the enemy vector according to an index
	bool GetIndexedMoveLeft(int _index) { return projectileVector[_index].gameObject->GetMoveLeft(); }
	//Returns the glassEnd variable from an element of the enemy vector according to an index
	bool GetIndexedGlassEnd(int _index) { return projectileVector[_index].gameObject->GetGlassEnd(); }
	//Sets the destroy variable from an element of the enemy vector according to an index
	void SetIndexedDestroy(int _index, bool _destroy) { projectileVector[_index].gameObject->SetDestroy(_destroy); }

	//Clears the vector
	void ClearVector();

	void Update();
	void Draw() {}
};