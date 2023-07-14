#include "stdafx.h"
#include "Building.h"
#include "rapidcsv.h"

void Building::SetBuildingInfo(Types type)
{
	this->type = type;

	rapidcsv::Document doc("Scripts/BuildingInfoList.csv");
	

}
