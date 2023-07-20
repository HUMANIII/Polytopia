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


	GameObject* selectedTile = nullptr;

	int score = 0;
	int stars = 0;

	float timer = 0.f;
public:
	Player(PlayerType type) :type(type){ };
	virtual ~Player() override { Release(); }

	PlayerType GetPlayerType() { return type; }
	int GetStars() { return stars; }
	void AddStars(int amount) { stars += amount; }

	//void SummonUnit();

	virtual void Init() override;

	virtual void Reset() override;

	virtual void Update(float dt) override;

	virtual void Draw(sf::RenderWindow& window) override;

	virtual bool SpecificUpdate(float dt) override;
	virtual void SwitchTurn();
};

