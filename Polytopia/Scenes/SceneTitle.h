#pragma once
#include "Scene.h"

class Player;

class SceneTitle :
    public Scene
{
protected:
	sf::View titleView;
	//float globalZoom = 1;

	sf::Vector2f interval = {256, 154};
	std::vector<MapTile*> tiles;
	
	MapTile* selectedTile = nullptr;
	GameObject* selectedTileOpt = nullptr;

	Player* player = nullptr;
	Player* enemy = nullptr;

	float timer;
public:
	SceneTitle(SceneId id = SceneId::Title);
	virtual ~SceneTitle() override;

	void SetSelectTile(float dt);
	GameObject* GetSelectTile() { return selectedTileOpt; }

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void SwitchTurn();
};

