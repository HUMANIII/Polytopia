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
    Player* player = nullptr;
    Player::PlayerType playerType = Player::PlayerType::Default;
    MapTile* tile = nullptr;
    City* belongedCity = nullptr;

    int cost = 0;
    int maxHp = 0;
    int hp = 0;
    int atk = 0;
    int def = 0;
    int defBonus = 1;
    int moveRange = 0;
    int atkRange = 0;
    std::string uiTextureId;

    bool canDash = false;
    bool canFortyfy = false;
    bool canEscape = false;
    bool canPersist = false;
    bool canRangeAtk = false;

    sf::Text hpUi;
    std::stringstream uiStream;
    sf::Sprite typeUi;

    State state = State::CanNotihng;
public:
    Unit();

    std::function<void()> testCode = [this]() {};

    virtual ~Unit() override = default;

    int GetCost() { return cost; }
    int GetAtkRange() { return atkRange; }
    int GetMoveRange() { return moveRange; }
    Player::PlayerType GetPlayerType() { return playerType; }

    void SetUnitInfo(Unit::UnitType UnitType, Player* player =nullptr, City* city = nullptr);
    void SetTileInfo(MapTile* tile) { this->tile = tile; }

    virtual void SetPosition(const sf::Vector2f& p);
    virtual void SetPosition(float x, float y);

    bool Action(MapTile* towards);
    bool Attack(Unit* opponent);
    bool Move(MapTile* towards);

    void Die();
    
    virtual void Reset() override;
    virtual void Update(float dt);
    virtual bool SpecificUpdate(float dt);
    virtual void Draw(sf::RenderWindow& window) override;
    virtual void SwitchTurn();
};

