#pragma once
#include "SpriteGo.h"
#include "Player.h"

//class Player;

class Unit :
    public SpriteGo
{
public:
    static enum class Type
    {
        Default = -1,
        Warrior,
        Archer,
        Defender,
        Rider,
        MindBender,
        Swordman,
        Catapult,
        Knight,
        Giant,
        Count,
    };
    static enum class State
    {
        Default = -1,
        CanMoveAtk,
        CanAtk,
        CanNotihng,
        Count,
    };
protected:
    int maxHp = 0;
    int hp = 0;
    int atk = 0;
    int def = 0;
    int maxMove = 0;
    int atkRange = 0;

    bool canDash = false;
    bool canFortyfy = false;
    bool canEscape = false;
    bool canPersist = false;

    State state = State::CanNotihng;
public:
    void SetUnitInfo(Unit::Type UnitType, Player::Type playerType = Player::Type::Player);

    void Move();
    void Attack();

    virtual void Reset() override;
    virtual void Draw(sf::RenderWindow& window) override;

};

