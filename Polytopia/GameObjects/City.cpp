#include "stdafx.h"
#include "City.h"
#include "rapidcsv.h"
#include "Unit.h"
#include "Player.h"
#include "ResourceMgr.h"

City::City(MapTile* cityTile, bool isCapital)
	:SpriteGo("","city")
{
	origin = Origins::CUSTOM;
	this->cityTile = cityTile;
	SetPosition(cityTile->sprite.getPosition());
	this->isCapital = isCapital;
	sortLayer = 10;
}

void City::Conquer(Player* player)
{
	this->player = player;
	SetCityIfo();
	std::list<GameObject*> tiles;
	cityTile->GetScene()->FindGos(tiles, "tile");
	for (auto tile : tiles)
	{
		MapTile* mt = dynamic_cast<MapTile*>(tile);
		if (this->cityTile->CheckRange(mt, 0))
		{
			mt->SetCity(this, mt);
		}
	}
	//cityTile->GetOnTileUnit()->SetState(Unit::State::CanNotihng);
}

Unit* City::SpawnUnit(Unit::UnitType type)
{
	if (units.size() >= (size_t)level + 999)
	{
		std::cout << "유닛 생성에 한계에 도달했습니다." << std::endl;
		return nullptr;
	}
	Unit* unit = new Unit();
	units.push_back(unit);
	unit->SetUnitInfo(type, player, this);
	if (unit->GetCost() > player->GetStars())
	{
		units.pop_back();
		delete unit;
		std::cout << "생산에 필요한 자원이 부족합니다." << std::endl;
		return nullptr;
	}
	player->AddStars(-unit->GetCost());
	unit->SetPosition(position);
	unit->SetTileInfo(cityTile);
	unit->sprite.setColor({ 255,255,255,184 });
	std::cout << "유닛이 생성되었습니다." << std::endl;
	return unit;
}

void City::SetCityIfo()
{
	int pType;
	if (player != nullptr)
		pType = (int)player->GetPlayerType();
	else
		pType = 99;
	int iC = (int)isCapital;
	

	rapidcsv::Document doc("Scripts/CityInfoList.csv");
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<int>(0, i) == pType
			&& doc.GetCell<int>(1, i) == iC)
		{
			std::string path = doc.GetCell<std::string>(2, i);

			sprite.setScale(1, 1);
			sprite.setTexture(*RESOURCE_MGR.GetTexture(path), true);
			sf::Vector2f spriteSize = Utils::GetSprite(sprite);
			sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - spriteSize.x * 0.25f);
			sprite.setPosition(cityTile->sprite.getPosition());
		}
	}
}

void City::AddExp(int amount)
{
	exp += amount;
	if (exp > level + 1)
	{
		exp -= level + 1;
		level += 1;
		std::cout << "도시 레벨 업!" << std::endl;
	}
}

bool City::SpecificUpdate(float dt)
{
	/*
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad1))
	{
		if (player->GetPlayerType() != Player::PlayerType::Player)
			return true;
		if (cityTile->GetOnTileUnit() != nullptr)
		{
			std::cout << "타일에 이미 다른 유닛이 있습니다." << std::endl;
			return false;
		}		
		cityTile->SetUnit(SpawnUnit(Unit::UnitType::Warrior), cityTile);
		return true;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad2))
	{
		if (player->GetPlayerType() != Player::PlayerType::Player)
			return true;
		if (cityTile->GetOnTileUnit() != nullptr)
		{
			std::cout << "타일에 이미 다른 유닛이 있습니다." << std::endl;
			return false;
		}
		cityTile->SetUnit(SpawnUnit(Unit::UnitType::Archer), cityTile);
		return true;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad3))
	{
		if (player->GetPlayerType() != Player::PlayerType::Player)
			return true;
		if (cityTile->GetOnTileUnit() != nullptr)
		{
			std::cout << "타일에 이미 다른 유닛이 있습니다." << std::endl;
			return false;
		}
		cityTile->SetUnit(SpawnUnit(Unit::UnitType::Knight), cityTile);
		return true;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad4))
	{
		if (player->GetPlayerType() != Player::PlayerType::Player)
			return true;
		if (cityTile->GetOnTileUnit() != nullptr)
		{
			std::cout << "타일에 이미 다른 유닛이 있습니다." << std::endl;
			return false;
		}
		cityTile->SetUnit(SpawnUnit(Unit::UnitType::Rider), cityTile);
		return true;
	}
	*/
	return false;
}

void City::SwitchTurn()
{
	if (player == nullptr)
		return;
	player->AddStars(level + 1 + (isCapital ? 1 : 0));
}