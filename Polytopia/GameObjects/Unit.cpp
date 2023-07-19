#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "City.h"

Unit::Unit()
{
}

void Unit::SetUnitInfo(Unit::UnitType UnitType, Player::PlayerType playerType)
{
	type = UnitType;
	int unitIndex = (int)UnitType;
	int playerIndex = (int)playerType;

	std::vector<std::string>values;
	rapidcsv::Document doc("Scripts/UnitsInfoList.csv");

	std::vector<std::string> infos = Utils::GetInfos<int, int>(doc, unitIndex, playerIndex);

	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<int>(0, i) == unitIndex && doc.GetCell<int>(1, i) == playerIndex)
		{
			for (int j = 2; j < doc.GetColumnCount(); j++)
			{
				values.push_back(doc.GetCell<std::string>(j, i));
			}
		}
	}

	maxHp = stoi(values[1]);
	atk = stoi(values[2]);
	def = stoi(values[3]);
	maxMove = stoi(values[4]);
	atkRange = stoi(values[5]);
	canDash = stoi(values[6]);
	canFortyfy = stoi(values[7]);
	canEscape = stoi(values[8]);
	canPersist = stoi(values[9]);
	textureId = values[10];

	sortLayer = 10;
	
	Reset();
	
	sprite.setOrigin(Utils::GetSprite(sprite).x * 0.5f, Utils::GetSprite(sprite).y - 15.f);
}

bool Unit::MoveOrAttack(MapTile* onTile, MapTile* towards)
{
	switch (state)
	{
	case Unit::State::CanMoveAtk:

		break;
	case Unit::State::CanMove:
		break;
	case Unit::State::CanAtk:
		break;
	case Unit::State::CanNotihng:
		break;
	default:
		break;
	}
	return false;
}

void Unit::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
}

bool Unit::SpecificUpdate(float dt)
{
	return false;
}

void Unit::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Unit::SwitchTurn()
{
	state = State::CanMoveAtk;
}
