#include "stdafx.h"
#include "City.h"
#include "rapidcsv.h"
#include "Unit.h"
#include "Player.h"

Unit* City::SpawnUnit()
{
	Unit* unit = new Unit();
	units.push_back(unit);
	return unit;
}
