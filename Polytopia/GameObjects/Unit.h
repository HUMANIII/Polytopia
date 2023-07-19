#pragma once
#include "SpriteGo.h"
#include "Player.h"
#include "MapTile.h"
#include "SceneTitle.h"

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
        CanMove,
        CanAtk,
        CanNotihng,
        Count,
    };
protected:
    UnitType type = UnitType::Default;
    Player::PlayerType playerType = Player::PlayerType::Default;
    MapTile* tile = nullptr;

    int maxHp = 0;
    int hp = 0;
    int atk = 0;
    int def = 0;
    int defBonus = 1;
    int moveRange = 0;
    int atkRange = 0;

    bool canDash = false;
    bool canFortyfy = false;
    bool canEscape = false;
    bool canPersist = false;

    State state = State::CanNotihng;
public:
    Unit();

    std::function<void()> testCode = [this]() {
        std::cout << "HP : " << hp << std::endl;
    };

    virtual ~Unit() override = default;

    void SetUnitInfo(Unit::UnitType UnitType, Player::PlayerType playerType = Player::PlayerType::Player);
    void SetTileInfo(MapTile* tile) { this->tile = tile; }

    bool Action(MapTile* towards);
    bool Attack(Unit* opponent);
    bool Move(MapTile* towards);
    
    virtual void Reset() override;
    virtual bool SpecificUpdate(float dt);
    virtual void Draw(sf::RenderWindow& window) override;
    virtual void SwitchTurn();
};

