#include "stdafx.h"
#include "Building.h"
#include "rapidcsv.h"

void Building::SetBuildingInfo(Types type)
{
	this->type = type;
	int index = (int)type;

	rapidcsv::Document doc("Scripts/BuildingInfoList.csv");
	std::vector<std::string> infos;
	/*for (int i = 0; i < doc.GetColumnCount(); i++)
	{
		if (doc.GetCell<int>(0, i) == key && doc.GetCell<T1>(1, i) == key1 && doc.GetCell<T2>(2, i) == key2)
		{
			for (int j = 3; j < doc.GetRowCount(); j++)
			{
				infos.push_back(doc.GetCell<std::string>(j, i));
			}
			break;
		}
	}*/

}
