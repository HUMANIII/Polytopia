#include "stdafx.h"
#include "City.h"
#include "rapidcsv.h"
#include "Player.h"
#include "Unit.h"

void City::SetCityInfo(City::player player)
{

}

Unit* City::SpawnUnit(Unit::Type unitType, Player::Type owner)
{
	if (level + 1 < units.size())
		return;
	Unit* unit = new Unit(this);
	unit->SetUnitInfo(unitType, owner); 
	unit->SetPosition(this->position);
	unit->sortLayer = 8;
	units.push_back(unit);
	return unit;
}
