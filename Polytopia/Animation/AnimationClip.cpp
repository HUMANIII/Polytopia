#include "stdafx.h"
#include "AnimationClip.h"
#include "rapidcsv.h"

bool AnimationClip::loadFromFile(const std::string& path)
{
    rapidcsv::Document doc(path,rapidcsv::LabelParams(-1,-1));
    id = doc.GetCell<std::string>(0, 1);
    fps = doc.GetCell<int>(1, 1);
    loopType = (AnimationLoopType)doc.GetCell<int>(2, 1);

    for (int i = 4; i < doc.GetRowCount(); i++)
    {
        auto row = doc.GetRow<std::string>(i);
        frames.push_back({ 
            row[0], 
            {std::stoi(row[1]), std::stoi(row[2]) , std::stoi(row[3]), std::stoi(row[4]) } });
    }
    return true;
}
