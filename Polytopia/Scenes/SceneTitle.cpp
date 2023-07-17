#include "stdafx.h"
#include "SceneTitle.h"
#include "ResourceMgr.h"
#include "TextGo.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "SpriteGo.h"
#include "Framework.h"
#include "DataTableManager.h"
#include "StringTable.h"
//#include "Player2.h"
#include "Player.h"
#include "RectGo.h"
#include "UIButton.h"
#include "MapTile.h"
#include "Unit.h"

SceneTitle::SceneTitle(SceneId id)
	: Scene(SceneId::Title)
{
	resourceListPath = "Scripts/SceneTitleResourceList.csv";
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	Release();

	/*
	SpriteGo* bgrnd = (SpriteGo*)AddGo(new SpriteGo("graphics/background.png","backgound"));
	bgrnd->SetOrigin(Origins::MC);
	bgrnd->sortLayer = -10;

	Player2* player = (Player2*)AddGo(new Player2("", "player"));
	UIButton* btn = (UIButton*)AddGo(new UIButton("graphics/btn_slide_no.png"));
	btn->SetOrigin(Origins::TR);
	btn->sortLayer = 105;
	btn->SetPosition(FRAMEWORK.GetWindowSize().x, 0.f);
	btn->OnClick = []()
	{std::cout << "click" << std::endl; };
	btn->OnEnter = [btn]()
	{
		std::cout << "enter" << std::endl; 
		btn->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/btn_slide_dim.png"));
	};
	btn->OnExit = [btn]()
	{
		std::cout << "exit" << std::endl; 
		btn->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/btn_slide_no.png"));
	};
	*/
	for (auto go : gameObjects)
	{
		go->Init();
	}	
}

void SceneTitle::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneTitle::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSize();
	worldView.setSize(windowSize);
	worldView.setCenter(0, 0);
	uiView.setSize(windowSize);
	uiView.setCenter(windowSize / 2.f);
	//worldView.zoom(5);
	/*
	Player2* player = (Player2*)FindGo("player");
	player->SetOrigin(Origins::BC);
	*/
	Scene::Enter();
	MapTile* MT = (MapTile*)AddGo(new MapTile());
	MT->SetScene(this);
	MT->SetTileInfo(MapTile::Base::Field, MapTile::Environment::Crop, MapTile::Resource::Fruits);
	MT->SetDraw();
	MT->SetPosition({ 0,0 });
	Unit* unit = (Unit*)AddGo(new Unit());
	unit->SetUnitInfo(Unit::Type::Warrior);	
	MT->SetUnit(unit);
	MT = (MapTile*)AddGo(new MapTile());
	MT->SetScene(this);
	MT->SetTileInfo(MapTile::Base::Field, MapTile::Environment::Default, MapTile::Resource::Tribe);
	MT->SetDraw();
	MT->SetPosition(interval * 0.5f);
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	INPUT_MGR.SwipeMap(worldView,sf::Mouse::Left);	
	//INPUT_MGR.ZoomMap(worldView, globalZoom);
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}
