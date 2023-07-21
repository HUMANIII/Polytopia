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
#include "Player.h"
#include "RectGo.h"
#include "UIButton.h"
#include "MapTile.h"
#include "Unit.h"
#include "City.h"

SceneTitle::SceneTitle(SceneId id)
	: Scene(SceneId::Title)
{
	resourceListPath = "Scripts/SceneTitleResourceList.csv";
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::SetSelectTile(float dt)
{
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		if (selectedTile == nullptr || !selectedTile->SpecificUpdate(dt))
		{
			int count = 0;
			for (int i = 0; i <tiles.size(); i++)
			{
				if (tiles[i]->clickFuctionOpt() != nullptr)
				{
					selectedTile = tiles[i]->clickFuction();
					selectedTileOpt = tiles[i]->clickFuctionOpt();
				}
				else
					count++;
			}
			if (count == tiles.size())
			{
				selectedTile = nullptr;
				selectedTileOpt = nullptr;
			}

		}
	}
}

void SceneTitle::Init()
{
	Release();

	MapTile::SettingUiPath();
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
	RESOURCE_MGR.LoadFromCSVFile(resourceListPath);

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
	

	player = (Player*)AddGo(new Player(Player::PlayerType::Player));
	enemy = (Player*)AddGo(new Player(Player::PlayerType::Enemy));

	sf::Vector2f data[25] = 
	{	
						{+0,-4},
					{-1,-3},{+1,-3},
				{-2,-2},{+0,-2},{+2,-2},
			{-3,-1} ,{-1,-1},{1,-1},{+3,-1},
		{-4,+0},{-2,+0},{+0,+0},{+2,+0},{+4,+0},
			{-3,+1},{-1,+1},{+1,+1},{+3,+1},
				{-2,+2},{+0,+2},{+2,+2},
					{-1,+3}, {+1,+3},
						{+0,+4},
	};

	for (int i = 0; i < sizeof(data)/ sizeof(sf::Vector2f); i++)
	{
		MapTile* MT = (MapTile*)AddGo(new MapTile());
		MT->Showup();

		MT->SetScene(this);
		MT->SetTileInfo(MapTile::Base::Field, MapTile::Environment::Crop, MapTile::Resource::Fruits);
		MT->SetDraw();
		MT->SetPosition(data[i]);
		if (i == 13)
		{
			City* city = new City(MT);
			MT->SetCity(city, MT);
			city->SetCityIfo();
			gameObjects.push_back(city);
			MT->SetTileInfo(MapTile::Base::Field);
			MT->SetDraw();
			MT->SetPosition(data[i]);
		}
		if (i == 5)
		{
			City* city = new City(MT,true);
			MT->SetCity(city, MT);
			city->Conquer(player);
			gameObjects.push_back(city);	
			MT->SetTileInfo(MapTile::Base::Field);
			MT->SetDraw();
			MT->SetPosition(data[i]);
		}
		if (i == 20)
		{
			Unit* unit = (Unit*)AddGo(new Unit());
			unit->SetUnitInfo(Unit::UnitType::Rider, enemy);
			unit->SetTileInfo(MT);
			MT->SetUnit(unit, MT);
		}

		tiles.push_back(MT);
	}

	UIButton* menu = (UIButton*)AddGo(new UIButton("menu"));

	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	timer += dt;
	if (timer > 2)
	{
		timer = 0;
		if (selectedTile != nullptr && selectedTileOpt != nullptr)
		{
			for (auto obj :	gameObjects)
			{
				Unit* object = dynamic_cast<Unit*>(obj);
				if (object != nullptr)
					object->testCode();
			}
			//std::cout << selectedTile->GetPosition().x << " , " << selectedTile->GetPosition().y << std::endl;
			std::cout << selectedTileOpt->GetPosition().x << " , " << selectedTileOpt->GetPosition().y << std::endl;
			if (dynamic_cast<City*>(selectedTileOpt))
			{
				std::cout << "µµ½Ã ¼±ÅÃµÊ" << std::endl;
			}
			if (dynamic_cast<Unit*>(selectedTileOpt))
			{
				std::cout << "À¯´Ö ¼±ÅÃµÊ" << std::endl;
			}
			if (dynamic_cast<MapTile*>(selectedTileOpt))
			{
				std::cout << "Å¸ÀÏ ¼±ÅÃµÊ" << std::endl;
			}

		}
	}
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f pos = ScreenToWorldPos(INPUT_MGR.GetMousePos());
		std::cout << pos.x << " , " << pos.y << std::endl;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0))
	{
		SwitchTurn();
	}

	INPUT_MGR.SwipeMap(worldView,sf::Mouse::Left);	
	//INPUT_MGR.ZoomMap(worldView, globalZoom);
	
	if (selectedTileOpt != nullptr)
	{
		prevTempTileOpt = selectedTileOpt;
		SetSelectTile(dt);
		currentTileOPT = selectedTileOpt;
		selectedTileOpt = prevTempTileOpt;
		if (!selectedTileOpt->SpecificUpdate(dt))
		{
			selectedTileOpt = currentTileOPT;
		}

	}
	else
	{
		SetSelectTile(dt);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTitle::SwitchTurn()
{
	std::cout << "ÅÏ ³Ñ±è" << std::endl;
	for (auto obj : gameObjects)
	{
		obj->SwitchTurn();
	}
}
