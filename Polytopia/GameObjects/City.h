#pragma once
#include "SpriteGo.h"
#include "Unit.h"

//class Unit;
class Player;

class City :
    public SpriteGo
{
public: 

protected:
    Player* player = nullptr;
    std::list<Unit*> units;
        
    int level = 1;
    bool isCapital = false;
    MapTile* cityTile;

public:
    City(MapTile* cityTile);
    virtual ~City() override {};

    std::list<Unit*> GetUnits() { return units; }
    void Conquer(Player* player);
    Unit* SpawnUnit(Unit::UnitType type);
    void SetCityIfo();
    int GetStar() { return level + 1; }

    //virtual void Init() {};
    //virtual void Release() {};

    //virtual void Reset() {};
    //virtual void Update(float dt) {};
    virtual bool SpecificUpdate(float dt);
    //virtual void Draw(sf::RenderWindow& window) {};
    //virtual void SwitchTurn() {};
};

