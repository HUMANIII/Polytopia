#pragma once
#include "SpriteGo.h"
class UIButton :
    public SpriteGo
{
protected:
	bool isHover = false;

	sf::Sprite boundary;
	sf::Sprite CenterImg;
	sf::Text text;

public:
	UIButton(const std::string& n = "");
    virtual ~UIButton() override;

	void SetButtonInfo(std::vector<std::string> infos);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Reset() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	std::function<void()> OnClick; 
	std::function<void()> OnEnter;
	std::function<void()> OnExit;
};

