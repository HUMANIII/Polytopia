#include "stdafx.h"
#include "Unit.h"
#include "Player.h"

void Unit::SetUnitInfo(Unit::Type UnitType, Player::Type playerType)
{
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

	sortLayer = 4;
	
	Reset();
	
	sprite.setOrigin(Utils::GetSprite(sprite).x * 0.5f, Utils::GetSprite(sprite).y - 15.f);
}

void Unit::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
}

void Unit::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}
