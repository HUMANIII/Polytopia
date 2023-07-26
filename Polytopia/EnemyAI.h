#pragma once
#include "Unit.h"

class SceneTitle;

class EnemyAI : public Unit
{
protected:
    static City* targetCapital;
    static SceneTitle* scene;
public:
    EnemyAI(Player* enemy, Unit::UnitType type);
    virtual ~EnemyAI() {};

    Unit* FindAtkTarget();
    MapTile* FindMoveTile();
    //void SpawnEnemy(Player* enemy, MapTile* tile, UnitType type);

    static void Setinfo(SceneTitle* scene, City* cap);
        
    virtual void SwitchTurn();
};

