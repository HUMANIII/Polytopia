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
    static enum class Base
    {
        Default = -1,
        Field,
        Count,
    };
    static enum class Environment
    {
        Default = -1,
        Farm,
        Forest,
        Mountain,
        Crop,
        Ruins,
        Count,
    };
    static enum class Resource
    {
        Default = -1,
        Animal,
        Mine,
        Fruits,
        Metal,
        Count,
    };
protected:
    sf::ConvexShape clickBound;

    sf::Vector2f detectSize = { 128, 77 }; // clickBound 가로 세로 크기
    std::vector<sf::Vector2f> detectPoints;
    
    Unit* onTileUnit = nullptr;
    Player* oner = nullptr;
    Building* onTileBuilding = nullptr;
    Scene* scene = nullptr;

    sf::Vector2f spriteSize = { 256, 245 };// 스프라이트 크기 기준

    Base base = Base::Default;
    Environment env = Environment::Default;
    sf::Sprite envSprite;
    Resource res = Resource::Default;
    sf::Sprite resSprite;

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

    void SetTileInfo(Base base, Environment env = Environment::Default, Resource res = Resource::Default);
    void SetDraw();

    void SetPosition(sf::Vector2f pos);
    void SetDetectArea(sf::Vector2f center);

    void SetScene(Scene* scene) { this->scene = scene; }

    bool isPointInsideShape(sf::Vector2f point = INPUT_MGR.GetMousePos());
    
};

