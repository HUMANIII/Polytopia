#include "stdafx.h"
#include "EnemyAI.h"
#include "City.h"
#include "Player.h"
#include "SceneTitle.h"

City* EnemyAI::targetCapital = nullptr;
SceneTitle* EnemyAI::scene = nullptr;

Unit* EnemyAI::FindAtkTarget()
{
	std::vector<Unit*> finder;

	for (MapTile* targetTile : scene->GetTiles())
	{
		if (!targetTile->CheckRange(tile, atkRange))
			continue;
		if (targetTile->GetOnTileUnit() != nullptr && targetTile->GetOnTileUnit() != this)
		{
			finder.push_back(targetTile->GetOnTileUnit());
		}
	}
	if (!finder.empty())
	{
		for (Unit* attackTarget : finder)
		{
			if (attackTarget->GetUnitType() == UnitType::Archer)
				return attackTarget;
		}
		for (Unit* attackTarget : finder)
		{
			if (attackTarget->GetUnitType() == UnitType::Knight)
				return attackTarget;
		}
		for (Unit* attackTarget : finder)
		{
			if (attackTarget->GetUnitType() == UnitType::Defender)
				return attackTarget;
		}
	}
	return nullptr;
}

MapTile* EnemyAI::FindMoveTile()
{
	std::vector<MapTile*> finder;
	MapTile* rtn = nullptr;

	for (MapTile* targetTile : scene->GetTiles())
	{
		if (!targetTile->CheckRange(tile, moveRange))
			continue;
		if (targetTile->GetOnTileUnit() == nullptr)
		{
			finder.push_back(targetTile);
		}
	}

	if (!finder.empty())
	{
		rtn = finder[0];
		sf::Vector2f capTilePos = targetCapital->GetTile()->GetTilePos();
		for (MapTile* moveTile : finder)
		{
			sf::Vector2f findPosL = rtn->GetTilePos() - capTilePos;
			sf::Vector2f findPosR = moveTile->GetTilePos() - capTilePos;
			if (abs(findPosL.x) + abs(findPosL.y) > abs(findPosR.x) + abs(findPosR.y))
				rtn = moveTile;
		}
	}
	return rtn;
}

EnemyAI::EnemyAI(Player* enemy, Unit::UnitType type)
	:Unit("enemyAI")
{
	player = enemy;
	playerType = Player::PlayerType::Enemy;

	SetUnitInfo(type, enemy);
	
}

void EnemyAI::Setinfo(SceneTitle* scene, City* cap)
{
	EnemyAI::scene = scene;
	EnemyAI::targetCapital = cap;
}
/*
void EnemyAI::SpawnEnemy(Player* enemy, MapTile* tile, UnitType type)
{
	EnemyAI* unit = (EnemyAI*)scene->AddGo(new EnemyAI(enemy, type));
	tile->SetUnit(this, tile);
	unit->SetPosition(tile->GetPosition());
}
*/
void EnemyAI::SwitchTurn()
{
	
	if (tile->GetCity() != nullptr)
	{
		if (tile->GetCity()->GetPlayer() != nullptr)
		{
			if (tile->GetCity()->GetPlayer()->GetPlayerType() == Player::PlayerType::Player)
			{
				tile->GetCity()->Conquer(player);
				return;
			}
		}
	}
	SpriteGo* target = FindAtkTarget();
	if (target != nullptr)
	{
		Attack(dynamic_cast<Unit*>(target));
		return;
	}
	target = FindMoveTile();
	if (target != nullptr)
	{
		Move(dynamic_cast<MapTile*>(target));
	}
	target = FindAtkTarget();
	if (target != nullptr)
	{
		Attack(dynamic_cast<Unit*>(target));
		return;
	}
	return;
}
