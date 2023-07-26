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
#include "City.h"
#include "UIText.h"
#include "EnemyAI.h"

SceneTitle::SceneTitle(SceneId id)
	: Scene(SceneId::Title), waveDoc("Scripts/WaveInfoList.csv")
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
		std::cout << "clicked"<<std::endl;
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
	if (INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
	{	
		for (auto button : PUI->GetButtons())
		{
			RemoveGo(button);
		}
		PUI->CallPopUpUI(selectedTileOpt);
		for (auto button : PUI->GetButtons())
		{
			gameObjects.push_back(button);
		}
	}

}

void SceneTitle::Init()
{
	Release();

	MapTile::SettingUiPath();
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
	

	player = (Player*)AddGo(new Player(Player::PlayerType::Player));
	enemy = (Player*)AddGo(new Player(Player::PlayerType::Enemy));
	rapidcsv::Document doc("Scripts/MapInfoList.csv");

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		std::vector<std::string> mapSetting = doc.GetRow<std::string>(i);
		MapTile* MT = (MapTile*)AddGo(new MapTile());
		MT->ShowUp();
		MT->SetScene(this);
		MT->SetTileInfo(static_cast<MapTile::Base>(stoi(mapSetting[2])), static_cast<MapTile::Environment>(stoi(mapSetting[3])), static_cast<MapTile::Resource>(stoi(mapSetting[4])));
		MT->SetDraw();
		MT->SetPosition(std::stof(mapSetting[0]), std::stof(mapSetting[1]));
		if (mapSetting[5] == "1")
		{
			City* city;
			if (mapSetting[6] == "1")
			{
				city = new City(MT,true);
				MT->SetCity(city, MT);
				city->Conquer(player);
				EnemyAI::Setinfo(this, city);
			}
			else
			{
				city = new City(MT);
				MT->SetCity(city, MT);
			}
			city->SetCityIfo();
			gameObjects.push_back(city);
			MT->SetTileInfo(MapTile::Base::Field);
			MT->SetDraw();
			MT->SetPosition(std::stof(mapSetting[0]), std::stof(mapSetting[1]));
		}
		tiles.push_back(MT);
	}
	/*
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
		MT->ShowUp();

		MT->SetScene(this);
		MT->SetTileInfo(MapTile::Base::Field, MapTile::Environment::Default, MapTile::Resource::Animal);
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
		if (i == 20 || i == 10 || i == 8)
		{
			Unit* unit = (Unit*)AddGo(new Unit());
			unit->SetUnitInfo(Unit::UnitType::Rider, enemy);
			unit->SetTileInfo(MT);	
			MT->SetUnit(unit, MT);
		}

		tiles.push_back(MT);
	}
	*/
	for (MapTile* tile : tiles)
	{
		tile->SetNearTile();
	}


	
	UIButton* UI = (UIButton*)AddGo(new UIButton("menu"));
	UI->SetPosition(windowSize.x * 2 / 6, windowSize.y - 100);
	UI = (UIButton*)AddGo(new UIButton("endTurn"));
	UI->SetPosition(windowSize.x * 4 / 6, windowSize.y - 100);
	UI->OnClick = [this]() {SwitchTurn(); };

	UIText* UT = (UIText*)AddGo(new UIText("turn"));
	UT->SetPosition(windowSize.x * 3 / 8, 100);	
	UT->SetChangingText(turn);
	UT = (UIText*)AddGo(new UIText("wave"));
	UT->SetPosition(windowSize.x * 4 / 8, 100);
	UT->SetChangingText(wave);
	UT = (UIText*)AddGo(new UIText("star"));
	UT->SetPosition(windowSize.x * 5 / 8, 100);
	UT->SetChangingText(player->GetStars());



	PUI = (PopUpUI*)AddGo(new PopUpUI());
	gameObjects.push_back(PUI);
	
	Scene::Enter();

	SwitchTurn();
}

void SceneTitle::Exit()
{
	for (auto tile : tiles)
	{
		tile->Release();
	}
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	timer += dt;
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f pos = ScreenToWorldPos(INPUT_MGR.GetMousePos());
		std::cout << pos.x << " , " << pos.y << std::endl;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad0))
	{
		SwitchTurn();
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::W))
	{
		StartWave();
	}
	/*
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::F10))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
	*/

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

MapTile* SceneTitle::FindTile(sf::Vector2f pos)
{
	for (MapTile* tile : tiles)
	{
		if(tile->GetTilePos() == pos)
			return tile;
	}
	return nullptr;
}

//void SceneTitle::SpawnEnemy(/*Player* enemy,*/ MapTile* tile, Unit::UnitType type)
void SceneTitle::SpawnEnemy(MapTile* tile, Unit::UnitType type)
{
	if (tile->GetOnTileUnit() != nullptr)
		return;
	EnemyAI* unit =(EnemyAI*)AddGo(new EnemyAI(enemy, type));
	tile->SetUnit(unit, tile);
	unit->SetPosition(tile->GetPosition());
	unit->SetTileInfo(tile);
}

void SceneTitle::StartWave()
{
	std::vector<float> coordXs;
	std::vector<float> coordYs;
	std::vector<int> unitTypes;
	wave++;

	for (int i = 0;i < waveDoc.GetRowCount(); i++)
	{
		if ((waveDoc.GetCell<int>(0, i)) <= wave)
		{
			coordXs.push_back(waveDoc.GetCell<float>(1, i));
			coordYs.push_back(waveDoc.GetCell<float>(2, i));
			unitTypes.push_back(waveDoc.GetCell<int>(3, i));
		}
	}
	for (int i = 0; i < coordXs.size(); i++)
	{
		SpawnEnemy(FindTile({ coordXs[i],coordYs[i]}), static_cast<Unit::UnitType>(unitTypes[i]));
	}
	isInWave = true;
}

void SceneTitle::SwitchTurn()
{
	std::cout << "턴 넘김" << std::endl;
	turn++;
	int leftEnemy = 0;
	bool hasCapital = false;
	for (auto obj : gameObjects)
	{
		obj->SwitchTurn();
	}

	if (!isInWave)
	{
		StartWave();
	}
	std::list<GameObject*> unitsList;
	std::list<GameObject*> citiesList;
	FindGos(unitsList, "unit");
	FindGos(citiesList, "city");

	for (GameObject* unit : unitsList)
	{
		if (dynamic_cast<Unit*>(unit)->GetPlayerType()
			== Player::PlayerType::Enemy)
			leftEnemy++;
	}

	for (GameObject* city : citiesList)
	{
		if(dynamic_cast<City*>(city)->GetPlayer()->GetPlayerType() == Player::PlayerType::Player)
			hasCapital = hasCapital || dynamic_cast<City*>(city)->GetIsCapital();
	}

	if (!hasCapital)
	{
		std::cout << "게임 종료" << std::endl;
	}
	if (leftEnemy == 0)
	{
		isInWave = false;
	}
}
