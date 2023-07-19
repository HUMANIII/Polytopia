#include "stdafx.h"
#include "City.h"
#include "rapidcsv.h"
#include "Unit.h"
#include "Player.h"
#include "ResourceMgr.h"

City::City(MapTile* cityTile)
{
	this->cityTile = cityTile;
	SetPosition(cityTile->sprite.getPosition());
	sortLayer = 10;
}

void City::Conquer(Player* player)
{
	this->player = player;
	SetCityIfo();
}

Unit* City::SpawnUnit(Unit::UnitType type)
{
	if (units.size() >= (size_t)level + 1)
		return nullptr;
	Unit* unit = new Unit();
	units.push_back(unit);
	unit->SetUnitInfo(type);
	unit->SetPosition(position);
	return unit;
}

void City::SetCityIfo()
{
	int pType = (int)player->GetPlayerType();
	int iC = (int)isCapital;
	

	rapidcsv::Document doc("Scripts/CityInfoList.csv");
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<int>(0, i) == pType
			&& doc.GetCell<int>(1, i) == iC)
		{
			std::string path = doc.GetCell<std::string>(2, i);

			sprite.setScale(1, 1);
			sprite.setTexture(*RESOURCE_MGR.GetTexture(path));
			sf::Vector2f spriteSize = Utils::GetSprite(sprite);
			sprite.setOrigin(spriteSize.x * 0.5f, spriteSize.y - spriteSize.x * 0.25f);
			sprite.setPosition(cityTile->sprite.getPosition());
		}
	}
}

bool City::SpecificUpdate(float dt)
{
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad1)
		&&player->GetPlayerType() == Player::PlayerType::Player)
	{
		if (cityTile->IsUnitOnTile())
		{
			std::cout << "Error : this tile has Unit" << std::endl;
			return false;
		}
		std::cout << "job`s Done" << std::endl;
		cityTile->SetUnit(SpawnUnit(Unit::UnitType::Warrior), cityTile);
		return true;
	}
	return false;
}
