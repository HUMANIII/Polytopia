#include "stdafx.h"
#include "City.h"
#include "rapidcsv.h"
#include "Unit.h"
#include "Player.h"
#include "ResourceMgr.h"

City::City(MapTile* cityTile, bool isCapital)
{
	this->cityTile = cityTile;
	SetPosition(cityTile->sprite.getPosition());
	this->isCapital = isCapital;
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
	{
		std::cout << "���� ������ �Ѱ迡 �����߽��ϴ�." << std::endl;
		return nullptr;
	}
	Unit* unit = new Unit();
	units.push_back(unit);
	unit->SetUnitInfo(type, player->GetPlayerType(), this);
	if (unit->GetCost() > player->GetStars())
	{
		units.pop_back();
		delete unit;
		std::cout << "���꿡 �ʿ��� �ڿ��� �����մϴ�." << std::endl;
		return nullptr;
	}
	player->AddStars(-unit->GetCost());
	unit->SetPosition(position);
	unit->SetTileInfo(cityTile);
	std::cout << "������ �����Ǿ����ϴ�." << std::endl;
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
	
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Numpad1))
	{
		if (player->GetPlayerType() != Player::PlayerType::Player)
			return true;
		if (cityTile->GetOnTileUnit() != nullptr)
		{
			std::cout << "Ÿ�Ͽ� �̹� �ٸ� ������ �ֽ��ϴ�." << std::endl;
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
			std::cout << "Ÿ�Ͽ� �̹� �ٸ� ������ �ֽ��ϴ�." << std::endl;
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
			std::cout << "Ÿ�Ͽ� �̹� �ٸ� ������ �ֽ��ϴ�." << std::endl;
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
			std::cout << "Ÿ�Ͽ� �̹� �ٸ� ������ �ֽ��ϴ�." << std::endl;
			return false;
		}
		cityTile->SetUnit(SpawnUnit(Unit::UnitType::Rider), cityTile);
		return true;
	}
	return false;
}

void City::SwitchTurn()
{
	player->AddStars(level + 1 + (isCapital ? 1 : 0));
}