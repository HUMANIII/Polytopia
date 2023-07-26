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
    enum class Base
    {
        Default = -1,
        Field,
        Count,
    };
    enum class Environment
    {
        Default = -1,
        Farm,
        Forest,
        Mountain,
        Crop,
        Ruins,
        Count,
    };
    enum class Resource
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
    sf::Sprite* envSprite = nullptr;
    Resource res = Resource::Default;
    sf::Sprite* resSprite = nullptr;

    sf::Sprite* UI;

    static std::vector<std::string> tileUiPathes;

    bool isHidden = true;
    bool canSee = false;

    int clickCount = 0;

    std::vector<MapTile*> nearTiles;
     
public:
    MapTile();
    virtual ~MapTile() override;

    //bool operator==(const MapTile& other) const;

    std::function<MapTile* ()> clickFuction = [this]() {return this; };
    std::function<GameObject* ()> clickFuctionOpt;

    static void SettingUiPath();

    void SetTileInfo(Base base, Environment env = Environment::Default, Resource res = Resource::Default);
    void SetDraw();

    void SetPosition(sf::Vector2f pos);
    void SetPosition(float x, float y);

    void SetScene(SceneTitle* scene) { this->scene = scene; }
    SceneTitle* GetScene() { return scene; }
    void SetUnit(Unit* unit, MapTile* tile);
    Unit* GetOnTileUnit() { return onTileUnit; }
    void SetCity(City* city, MapTile* tile);
    City* GetCity() { return cityBelonged; }
    sf::Sprite* GetUI() { return UI;}
    sf::Vector2f GetTilePos() { return tilePos; }
    void SetNearTile();
    std::vector<MapTile*>GetNearTiles() { return nearTiles; }
        
    void Harvest();
    void BuildBuilding();

    void Move(MapTile* tile);
    void ClearUnit() { onTileUnit = nullptr; }
    void ShowUp() { isHidden = false; }
    
    void Unselected();
    void UnitSelected();
    void CitySelected();
    void TileSelected();

    bool CheckRange(MapTile* otherTile, int range);
    bool CheckMoveRange(MapTile* otherTile, int range);
    bool isPointInsideShape(const sf::Shape& shape, sf::Vector2f point = INPUT_MGR.GetMousePos());

    void Release();
    
    virtual void Update(float dt) override;
    virtual bool SpecificUpdate(float dt);
    virtual void Draw(sf::RenderWindow& window) override;
    //virtual void SwitchTurn();
};

