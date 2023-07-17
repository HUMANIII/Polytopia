#pragma once
#include "SpriteGo.h"

class Player;
class Unit;

class City :
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
    player owner = City::player::Default;
    std::list<Unit*> units;
        
    int level = 0;
    bool isCapital = false;

public:
    City();
    ~City();

    void SetCityInfo(City::player player);

    Unit* SpawnUnit(Unit::Type unitType, Player::Type owner);
};

