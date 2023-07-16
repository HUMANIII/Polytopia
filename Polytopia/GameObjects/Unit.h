#pragma once
#include "SpriteGo.h"
class Unit :
    public SpriteGo
{
public:
    static enum class Type
    {
        Warrior,
        Archer,
        Defender,
        Rider,
        MindBender,
        Swordmas,
        Catapult,
        Knight,
        Giant,
        Count,
    };
protected:
    int hp;
    int atk;
    int def;
    int maxMove;
    int atkRange;

    bool canFortyfy;
    bool canDash;
    bool canEscape;
    bool canPersist;
public:
};

