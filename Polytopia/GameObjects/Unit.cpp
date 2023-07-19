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
	this->playerType = playerType;
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
	moveRange = stoi(values[4]);
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

bool Unit::Action(MapTile* towards)
{	
	switch (state)
	{
	case Unit::State::CanMoveAtk:		
		if (towards->GetOnTileUnit() != nullptr &&
			towards->GetOnTileUnit()->playerType == Player::PlayerType::Enemy)
			return Attack(towards->GetOnTileUnit());
		return Move(towards);
		break;
	case Unit::State::CanMove:
		return Move(towards);
		break;
	case Unit::State::CanAtk:
		return Attack(towards->GetOnTileUnit());
		break;
	case Unit::State::CanNotihng:
		std::cout << "행동 할 수 없는 상태입니다." << std::endl;
		return false;
		break;
	}
}


bool Unit::Attack(Unit* opponent)
{
	if (opponent == nullptr)
	{
		std::cout << "공격대상이 없습니다." << std::endl;
		return false;
	}
	if (!tile->CheckRange(opponent->tile, atkRange))
	{
		std::cout << "공격거리 밖입니다." << std::endl;
		return false;
	}
	if (opponent->playerType != Player::PlayerType::Enemy)
	{
		std::cout << "적이 아닙니다" << std::endl;
		return false;
	}
	float atkForce = (float)atk * ((float)hp / maxHp);
	float defForce = (float)opponent->def * ((float)opponent->hp / opponent-> maxHp) * opponent->defBonus;
	float totalDmg = atkForce + defForce;
	opponent->hp -= roundf((atkForce / totalDmg) * atk * 4.5f);
	state = State::CanNotihng;
	if (opponent->hp <= 0)
	{
		Move(opponent->tile);
		if (canPersist)
		{
			state = State::CanAtk;
		}
	}
	else
		hp -= roundf((defForce / totalDmg) * opponent->def * 4.5f);
	if (canEscape)
		state = State::CanMove;
	std::cout << "공격 성공" << std::endl;
	return true;
}

bool Unit::Move(MapTile* towards)
{
	if (!tile->CheckRange(towards, moveRange))
	{
		std::cout << "이동거리 밖입니다." << std::endl;
		return false;
	}
	if(towards->GetOnTileUnit() != nullptr)
	{
		std::cout << "이동할 장소에 다른 유닛이 있습니다." << std::endl;
		return false;
	}
	tile->Move(towards);
	tile = towards;
	SetPosition(towards->GetPosition());
	if (canDash)
		state = State::CanAtk;
	else
		state = State::CanNotihng;
	std::cout << "이동 성공" << std::endl;
	return true;
}

void Unit::Reset()
{
	SpriteGo::Reset();
	hp = maxHp;
}

bool Unit::SpecificUpdate(float dt)
{	
	if (INPUT_MGR.GetMouseButtonDown(sf::Mouse::Left))
	{
		if(this->playerType == Player::PlayerType::Player)
			return Action(tile->GetScene()->GetSelectTile());
		std::cout << "당신의 유닛이 아닙니다." << std::endl;
		return false;
	}
}

void Unit::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void Unit::SwitchTurn()
{
	state = State::CanMoveAtk;
}
