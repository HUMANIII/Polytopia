#include "stdafx.h"
#include "Unit.h"
#include "Player.h"
#include "City.h"
#include "ResourceMgr.h"
#include "SceneTitle.h"
#include "MapTile.h"

Unit::Unit(std::string name)
	:SpriteGo("", name)
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
	std::vector<std::string>fonts;
	rapidcsv::Document doc("Scripts/UnitsInfoList.csv");
	rapidcsv::Document fontDoc("Scripts/FontInfoList.csv");

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
	/*
	for (int i = 0; i < fontDoc.GetRowCount(); i++)
	{
		if (fontDoc.GetCell<std::string>(0, i) == "default")
		{
			for (int j = 2; j < fontDoc.GetColumnCount(); j++)
			{
				fonts.push_back(fontDoc.GetCell<std::string>(j, i));
			}
		}
	}
	*/
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
	attackMethod.setTexture(*RESOURCE_MGR.GetTexture(values[17]));

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
	if (opponent->GetPlayerType() == GetPlayerType())
	{
		std::cout << "적이 아닙니다" << std::endl;
		return false;
	}
	float atkForce = (float)atk * ((float)hp / maxHp);
	float defForce = (float)opponent->def * ((float)opponent->hp / opponent-> maxHp) * opponent->defBonus;
	float totalDmg = atkForce + defForce;
	timer = 0;
	startPosition = position;
	endPosition = opponent->GetPosition();
	isAttacking = true;
	opponent->hp -= roundf((atkForce / totalDmg) * atk * 4.5f);
	if (tile->GetPosition().x < position.x)
	{
		sprite.setScale({ -1, 1 });
	}
	if (tile->GetPosition().x > position.x)
	{
		sprite.setScale({ 1, 1 });
	}
	state = State::CanNotihng;
	sprite.setColor({ 255,255,255,184 });
	if (opponent->hp <= 0)
	{
		MapTile* temp = opponent->tile;
		opponent->Die();
		if(!canRangeAtk)
			Move(temp);
		if (canPersist)
		{
			state = State::CanAtk;
			sprite.setColor({ 255,255,255,255 });
		}
	}
	else
	{
		if (tile->CheckRange(opponent->tile, opponent->atkRange))
		{
			opponent->SetCounterAttack(position, opponent->position);
			hp -= roundf((defForce / totalDmg) * opponent->def * 4.5f);
		}
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
	if (tile->GetPosition().x < position.x)
	{
		sprite.setScale({ -1, 1 });
	}
	if (tile->GetPosition().x > position.x)
	{
		sprite.setScale({ 1, 1 });
	}
	//SetPosition(towards->GetPosition());
	timer = 0;
	startPosition = position;
	endPosition = towards->GetPosition();
	isMoving = true;
	if (canDash)
		state = State::CanAtk;
	else
	{
		state = State::CanNotihng;
		sprite.setColor({ 255,255,255,184 });
	}
	std::cout << "이동 성공" << std::endl;
	return true;
}

/*
bool Unit::Move(MapTile* towards)
{
	if (!tile->CheckMoveRange(towards, moveRange))
	{
		std::cout << "이동 불가" << std::endl;
		return false;
	}
	tile->Move(towards);
	tile = towards;
	if (tile->GetPosition().x < position.x)
	{
		sprite.setScale({ -1, 1 });
	}
	if (tile->GetPosition().x > position.x)
	{
		sprite.setScale({ 1, 1 });
	}
	timer = 0;
	startPosition = position;
	endPosition = towards->GetPosition();
	isMoving = true;
	if (canDash)
		state = State::CanAtk;
	else
	{
		state = State::CanNotihng;
		sprite.setColor({ 255,255,255,184 });
	}
	std::cout << "이동 성공" << std::endl;
	return true;
}
*/
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
	if (isAttacking)
		window.draw(attackMethod);
}

void Unit::SwitchTurn()
{
	state = State::CanMoveAtk;
	sprite.setColor({ 255,255,255,255 });
}

void Unit::Update(float dt)
{
	SpriteGo::Update(dt);
	uiStream << hp;
	hpUi.setString(uiStream.str());
	uiStream.str("");	
	timer += dt;
	if (isMoving)
	{
		MoveMotion(endPosition);
	}
	if (isAttacking)
	{
		AttackMotion(endPosition);
	}
}

void Unit::Heal()
{
	if (state == State::CanAtk || state == State::CanMoveAtk)
	{
		hp += 4;
		if (maxHp < hp)
			hp = maxHp;
		state = State::CanNotihng;
		sprite.setColor({ 255,255,255,184 });
		std::cout << "치유됨" << std::endl;
	}
}

void Unit::MoveMotion(sf::Vector2f p)
{		
	SetPosition(Utils::Lerp(startPosition, p, timer * 4, false));
	if (timer > 0.25)
	{
		isMoving = false;
		timer = 0;
		position = p;
	}
}

void Unit::MoveMotion(float x, float y)
{
	MoveMotion({ x,y });
}

void Unit::AttackMotion(sf::Vector2f p)
{
	if (type == UnitType::Archer || type == UnitType::Catapult)
	{
		atkStandardAngle = Utils::Angle(endPosition - startPosition);
		attackMethod.setRotation(atkStandardAngle);
		attackMethod.setPosition(Utils::Lerp(startPosition, p, timer * 4, false));
		if (timer > 0.25)
		{
			isAttacking = false;
			timer = 0;
		}
	}
	else
	{
		atkStandardAngle = Utils::Angle(endPosition - startPosition);
		sf::Vector2f spriteSize = { attackMethod.getLocalBounds().width, attackMethod.getLocalBounds().height };
		attackMethod.setOrigin(spriteSize.x *0.5f , spriteSize.y + 35.f);
		attackMethod.setPosition(position);
		attackMethod.setRotation(atkStandardAngle + timer * 720);
		if (timer > 0.25)
		{
			isAttacking = false;
			timer = 0;
		}
	}
}

void Unit::SetCounterAttack(sf::Vector2f target, sf::Vector2f starting)
{
	timer = 0;
	startPosition = starting;
	endPosition = target;
	isAttacking = true;
}

void Unit::AttackMotion(float x, float y)
{
	AttackMotion({ x,y });
}
