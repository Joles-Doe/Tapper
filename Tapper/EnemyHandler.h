#pragma once

#include "GameObject.h"
#include "Engine.h"
#include "Patron.h"

struct Enemy
{
	Enemy(std::shared_ptr<Patron> _input)
	{
		gameObject = _input;
	};
	std::shared_ptr<Patron> gameObject;
};

class EnemyHandler : public GameObject
{
private:
	Engine* engine{ nullptr };

	std::vector<Enemy> enemyVector;
	static bool EnemyPredicate(const Enemy& _input);
public:
	EnemyHandler(SDL_Renderer* _rend, Engine* _engine) : GameObject(_rend) { engine = _engine; }

	void AddEnemy(int _y, int _layer);

	int GetVectorSize() { return enemyVector.size(); }

	SDL_Rect GetIndexedRect(int _index) { return enemyVector[_index].gameObject->GetRect(); }

	void SetIndexedDestroy(int _index, bool _destroy) { enemyVector[_index].gameObject->SetDestroy(_destroy); }
	void SetIndexedLeave(int _index, bool _exit ) { enemyVector[_index].gameObject->SetLeave(_exit); }

	void Update();
	void Draw() {}
};

