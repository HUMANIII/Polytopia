#pragma once
#include "SpriteGo.h"
#include "Player.h"
#include "MapTile.h"

class City;
//class Player;

class Unit :
    public SpriteGo
{
public:
    static enum class UnitType
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
    UnitType type = UnitType::Default;
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
    Unit();
    virtual ~Unit() override = default;

    void SetUnitInfo(Unit::UnitType UnitType, Player::PlayerType playerType = Player::PlayerType::Player);

    
    virtual void Reset() override;
    virtual void Draw(sf::RenderWindow& window) override;

};

