#pragma once
#include "Unit.h"
#include "SceneTitle.h"

class EnemyAI :
    public Unit
{
protected:
    static City* targetCapital;
    static SceneTitle* scene;
    Unit* FindAtkTarget();
    MapTile* FindMoveTile();
public:
    EnemyAI(Player* enemy);
    virtual ~EnemyAI() override = default;

    static void Setinfo(SceneTitle* scene, City* cap);

    virtual void SwitchTurn();
};

