#pragma once
#include "SpriteGo.h"
#include "InputMgr.h"

class Unit;
class City;
class Player;
class SceneTitle;

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
    sf::Vector2f tilePos = { 0,0 };
    
    Unit* onTileUnit = nullptr;
    //Player* oner = nullptr;
    City* cityBelonged = nullptr;

    static SceneTitle* scene;

    Base base = Base::Default;
    Environment env = Environment::Default;
    sf::Sprite envSprite;
    Resource res = Resource::Default;
    sf::Sprite resSprite;

    sf::Sprite UI;

    bool isHidden = true;
    bool canSee = false;

    int clickCount = 0;

public:
    MapTile();
    virtual ~MapTile() override;

    std::function<MapTile* ()> clickFuction = [this]() {return this; };
    std::function<GameObject* ()> clickFuctionOpt;

    void SetTileInfo(Base base, Environment env = Environment::Default, Resource res = Resource::Default);
    void SetDraw();

    void SetPosition(sf::Vector2f pos);
    void SetScene(SceneTitle* scene) { this->scene = scene; }
    SceneTitle* GetScene() { return scene; }

    void SetUnit(Unit* unit, MapTile* tile);
    void ClearUnit() { onTileUnit = nullptr; }
    City* GetCity() { return cityBelonged; }
    void SetCity(City* city, MapTile* tile);
    void Move(MapTile* tile);
    Unit* GetOnTileUnit() { return onTileUnit; }
    sf::Vector2f GetTilePos() { return tilePos; }

    void Showup() { isHidden = false; }

    bool CheckRange(MapTile* otherTile, int range);
    bool isPointInsideShape(const sf::Shape& shape, sf::Vector2f point = INPUT_MGR.GetMousePos());
    
    virtual void Update(float dt) override;
    virtual bool SpecificUpdate(float dt);
    virtual void Draw(sf::RenderWindow& window) override;
    //virtual void SwitchTurn();
};

