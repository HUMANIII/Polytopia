#pragma once
#include "GameObject.h"
#include "UIButton.h"

class PopUpUI :
    public GameObject
{
protected:
    std::vector<UIButton*> buttons;
public:
    PopUpUI();
    virtual ~PopUpUI() override = default;
        
    void SetButtonInfo(GameObject* obj);

    std::vector<UIButton*> GetButtons() { return buttons; }

    virtual void SetPosition(const sf::Vector2f& p);
    virtual void SetPosition(float x, float y);

    void CallPopUpUI(GameObject* selected);
        
    virtual void Init() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual bool SpecificUpdate(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
    virtual void SwitchTurn() override;
};

