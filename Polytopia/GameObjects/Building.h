#pragma once
#include "SpriteGo.h"

class Player;

class Building :
    public SpriteGo
{
public: 
    static enum class player
    {
        Default = -1,
        player,
        enemy,
        Count,
    };

protected:
    player oner = Building::player::Default;
        
    int level = 0;

    bool isCapital = false;

public:
    Building();
    ~Building(); 

    void SetBuildingInfo(Building::player player);
};

