#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "City.h"
#include "ResourceMgr.h"

Unit::Unit()
{
	origin = Origins::CUSTOM;
}

void Unit::SetUnitInfo(Unit::UnitType UnitType, Player* player, City* city)
{
	belongedCity = city;
	type = UnitType;
	this->player = player;
	this->playerType = this->player->GetPlayerType();
	int unitIndex = (int)UnitType;
	int playerIndex = (int)playerType;

	std::vector<std::string>values;
	rapidcsv::Document doc("Scripts/UnitsInfoList.csv");

	//std::vector<std::string> infos = Utils::GetInfos<int, int>(doc, unitIndex, playerIndex);

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

	cost = stoi(values[0]);
	maxHp = stoi(values[1]);
	atk = stoi(values[2]);
	def = stoi(values[3]);
	moveRange = stoi(values[4]);
	atkRange = stoi(values[5]);
	canDash = stoi(values[6]);
	canFortyfy = stoi(values[7]);
	canEscape = stoi(values[8]);
	canPersist = stoi(values[9]);
	canRangeAtk = stoi(values[10]);
	textureId = values[11];
	typeUi.setTexture(*RESOURCE_MGR.GetTexture(values[12]));
	typeUi.setColor({ (sf::Uint8)stoi(values[13]) ,(sf::Uint8)stoi(values[14]) ,(sf::Uint8)stoi(values[15]) ,(sf::Uint8)stoi(values[16]) });
	hpUi.setFont(*RESOURCE_MGR.GetFont("fonts/JosefinSans-VariableFont_wght.ttf"));

	sortLayer = 10;
	
	Reset();

	sprite.setOrigin(Utils::GetSprite(sprite).x * 0.5f, Utils::GetSprite(sprite).y - 15.f);
	Utils::SetOrigin(hpUi, Origins::MC);
	Utils::SetOrigin(typeUi, Origins::MC);
}

bool Unit::Action(MapTile* towards)
{	
	if (towards == nullptr)
	{
		return false;
	}
	switch (state)
	{
	case Unit::State::CanMoveAtk:		
		if (towards->GetOnTileUnit() == nullptr) 
			return Move(towards);
		if(towards->GetOnTileUnit()->playerType == Player::PlayerType::Enemy)
			return Attack(towards->GetOnTileUnit());
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
		MapTile* temp = opponent->tile;
		opponent->Die();
		if(!canRangeAtk)
			Move(temp);
		if (canPersist)
			state = State::CanAtk;
	}
	else
	{
		hp -= roundf((defForce / totalDmg) * opponent->def * 4.5f);
		if (hp <= 0)
			Die();
	}

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

void Unit::SetPosition(const sf::Vector2f& p)
{
	position = p;
	sprite.setPosition(position);
	typeUi.setPosition(position.x + 50, position.y - 120);
	hpUi.setPosition(position.x - 75, position.y - 130);
}

void Unit::Die()
{
	if (belongedCity != nullptr)
	{
		belongedCity->GetUnits()->remove(this);
		belongedCity = nullptr;
	}
	tile->GetScene()->RemoveGo(this);
	tile->ClearUnit();
}

void Unit::SetPosition(float x, float y)
{
	SetPosition({ x, y });
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
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::C))
	{
		if (state == State::CanMoveAtk)
		{
			tile->GetCity()->Conquer(player);
			tile->GetCity()->SetCityIfo();
		}
	}
}

void Unit::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(hpUi);
	window.draw(typeUi);
}

void Unit::SwitchTurn()
{
	state = State::CanMoveAtk;
}

void Unit::Update(float dt)
{
	SpriteGo::Update(dt);
	uiStream << hp;
	hpUi.setString(uiStream.str());
	uiStream.str("");
}
