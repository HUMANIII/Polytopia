#pragma once
#include "GameObject.h"
class PopUpUI :
    public GameObject
{
protected:
    std::vector<UIButton*> buttons;
public:
    PopUpUI();
    virtual ~PopUpUI() override = default;

    void SetButtonInfo(GameObject* obj);

        // GameObject��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Reset() override;
    virtual void Update(float dt) override;
    virtual bool SpecificUpdate(float dt) override;
    virtual void Draw(sf::RenderWindow& window) override;
    virtual void SwitchTurn() override;
};

