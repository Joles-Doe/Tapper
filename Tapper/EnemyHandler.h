#pragma once

#include "GameObject.h"
#include "Engine.h"
#include "Patron.h"

//Custom struct used for predicate
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
	//Game engine
	Engine* engine{ nullptr };
	//Vector that stores a pointer of the enemies
	std::vector<Enemy> enemyVector;
	//Predicate used to determine if an element can be removed from the enemyVector
	static bool EnemyPredicate(const Enemy& _input);
public:
	EnemyHandler(SDL_Renderer* _rend, Engine* _engine) : GameObject(_rend) { engine = _engine; }
	~EnemyHandler();

	//Adds an enemy to the vector and engine
	void AddEnemy(int _y, int _layer);
	//Returns the size of the enemy vector
	int GetVectorSize() { return enemyVector.size(); }
	//Clears the vector
	void ClearVector() { enemyVector.clear(); }
	//Returns a rect from an element of the enemy vector according to an index
	SDL_Rect GetIndexedRect(int _index) { return enemyVector[_index].gameObject->GetRect(); }
	//Getters and Setters for the destroy variable from an element of the enemy vector according to an index
	bool GetIndexedDestroy(int _index) { return enemyVector[_index].gameObject->GetDestroy(); }
	void SetIndexedDestroy(int _index, bool _destroy) { enemyVector[_index].gameObject->SetDestroy(_destroy); }	
	//Getters and Setters for the leave variable from an element of the enemy vector according to an index
	bool GetIndexedLeave(int _index) { return enemyVector[_index].gameObject->GetLeave(); }
	void SetIndexedLeave(int _index, bool _exit ) { enemyVector[_index].gameObject->SetLeave(_exit); }
	//Getters and Setters for the return variable from an element of the enemy vector according to an index
	bool GetIndexedReturn(int _index) { return enemyVector[_index].gameObject->GetReturnDrink(); }
	void SetIndexedReturn(int _index, bool _return) { enemyVector[_index].gameObject->SetReturnDrink(_return); }
	//Returns the Y index from an element of the enemy vector according to an index
	int GetIndexedYIndex(int _index) { return enemyVector[_index].gameObject->GetYIndex(); }
	//Returns the reachendEnd variable from an element of the enemy vector according to an index
	bool GetIndexedReachedEnd(int _index) { return enemyVector[_index].gameObject->GetReachedEnd(); }

	void Update();
	void Draw() {}
};

