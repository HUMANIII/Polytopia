#include "stdafx.h"
#include "City.h"
#include "rapidcsv.h"
#include "Unit.h"
#include "Player.h"

Unit* City::SpawnUnit(Unit::UnitType type)
{
	if (units.size() <= (size_t)level + 1)
		return nullptr;
	Unit* unit = new Unit();
	units.push_back(unit);
	unit->SetUnitInfo(type);
	return unit;
}
