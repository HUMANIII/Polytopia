#pragma once
#include "SpriteGo.h"

class Unit;
class Player;

class City :
    public SpriteGo
{
public: 

protected:
    Player* player;
    std::list<Unit*> units;
        
    int level = 0;
    bool isCapital = false;

public:
    City() {}
    virtual ~City() override;

    //void Conquer(Player* player);
    Unit* SpawnUnit();
};

