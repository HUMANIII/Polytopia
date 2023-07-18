#pragma once
#include "GameObject.h"
#include "Unit.h"

//class Unit;
class Player;

class City :
    public GameObject
{
public: 

protected:
    Player* player = nullptr;
    std::list<Unit*> units;
        
    int level = 1;
    bool isCapital = false;

public:
    City() {}
    virtual ~City() override;

    std::list<Unit*> GetUnits() { return units; }
    void Conquer(Player* player) { this->player = player; }
    Unit* SpawnUnit(Unit::UnitType type);

    virtual void Init() {};
    virtual void Release() {};

    virtual void Reset() {};
    virtual void Update(float dt) {};
    virtual void Draw(sf::RenderWindow& window) {};
};

