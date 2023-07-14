#pragma once
#include "SpriteGo.h"
#include "InputMgr.h"

class Unit;
class Building;
class Player;
class Scene;

class MapTile :
    public SpriteGo
{
public:
    static enum class Types
    {
        Default = -1,
        FieldWithCrop,
    };
protected:
    sf::ConvexShape clickBound;

    sf::Vector2f detectSize = { 500,300 }; // clickBound 가로 세로 크기
    std::vector<sf::Vector2f> detectPoints;
    
    Unit* onTileUnit = nullptr;
    Player* oner = nullptr;
    Building* onTileBuilding = nullptr;
    Scene* scene = nullptr;

    sf::Vector2f spriteSize = { 1000, 950 };// 스프라이트 크기 기준

    Types type = Types::Default;

    bool isDiscovered = false;
    bool canSee = false;

    int clickCount = 0;

    std::function<void()> clickNone;
    std::function<void()> clickOnce;
    std::function<void()> clickTwice;
public:
    MapTile();
    virtual ~MapTile() override;

    virtual void Update(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;

    void SetTileInfo(Types type);

    void SetPosition(sf::Vector2f pos);
    void SetDetectArea(sf::Vector2f center);

    void SetScene(Scene* scene) { this->scene = scene; }

    bool isPointInsideShape(sf::Vector2f point = INPUT_MGR.GetMousePos());
    
};

