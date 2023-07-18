#pragma once
#include "GameObject.h"
#include "MapTile.h"

class City;

class Player : public GameObject
{
public:
	enum class PlayerType
	{
		Default = -1,
		Player,
		Enemy,
		Count,
	};

protected:
	PlayerType type = PlayerType::Default;

	std::list<City*> buildings;

	GameObject* selectedTile = nullptr;

	int score = 0;
	int stars = 0;
public:
	Player();
	virtual ~Player() override { Release(); }

	void SummonUnit();

	virtual void Init() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;

};

