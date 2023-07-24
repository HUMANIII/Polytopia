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
    int exp = 0;
    bool isCapital = false;
    MapTile* cityTile;

public:
    City(MapTile* cityTile, bool isCapital = false);
    virtual ~City() override {};

    std::list<Unit*>* GetUnits() { return &units; }
    void Conquer(Player* player);
    Unit* SpawnUnit(Unit::UnitType type);
    void SetCityIfo();
    Player* GetPlayer() { return player; }
    
    void AddExp(int amount);

    //virtual void Init() {};
    //virtual void Release() {};

    //virtual void Reset() {};
    //virtual void Update(float dt) {};
    virtual bool SpecificUpdate(float dt);
    //virtual void Draw(sf::RenderWindow& window) {};
    virtual void SwitchTurn();
};

