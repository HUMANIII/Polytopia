#pragma once
#include "SpriteGo.h"
#include "AnimationController.h"

class Unit;
class Building;

class Player : public GameObject
{
public:
	enum class Type
	{
		Default = -1,
		Player1,
		Player2,
		Count,
	};

protected:
	Type type = Type::Default;

	std::list<Unit*> units;
	std::list<Building*> buildings;

	int score = 0;
public:
	Player();
	virtual ~Player() override { Release(); }


	virtual void Init() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;

};

