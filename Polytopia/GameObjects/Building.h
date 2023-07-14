#pragma once
#include "SpriteGo.h"

class Player;

class Building :
    public SpriteGo
{
public: 
    enum class Types
    {
        Default = 0,
        Temple,
        Normal,
        Count,
    };
protected:
    Types type;
    Player* player;

    int score;

public:
    Building();
    ~Building(); 

    void SetBuildingInfo(Types type);
};

