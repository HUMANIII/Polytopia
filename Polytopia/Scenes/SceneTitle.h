#pragma once
#include "Scene.h"
#include "PopUpUI.h"

class Player;

class SceneTitle :
    public Scene
{
protected:
	sf::View backgroundView;
	float globalZoom = 1;
	
	std::vector<MapTile*> tiles;
	
	MapTile* selectedTile = nullptr;
	GameObject* selectedTileOpt = nullptr;
	GameObject* prevTempTileOpt = nullptr;
	GameObject* currentTileOPT = nullptr;

	Player* player = nullptr;
	Player* enemy = nullptr;
	PopUpUI* PUI = nullptr;

	float timer;

	int turn;
public:
	SceneTitle(SceneId id = SceneId::Title);
	virtual ~SceneTitle() override;

	void SetSelectTile(float dt);
	MapTile* GetSelectTile() { return selectedTile; }
	GameObject* GetSelectTileOpt() { return selectedTileOpt; }

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void SwitchTurn();

};

