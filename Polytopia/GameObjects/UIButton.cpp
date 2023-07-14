#include "stdafx.h"
#include "UIButton.h"
#include "SceneMgr.h"
#include "InputMgr.h"

UIButton::UIButton(const std::string& textureId, const std::string& n)
	:SpriteGo(textureId, n)
{
}

UIButton::~UIButton()
{
}

void UIButton::Init()
{
	SpriteGo::Init();
}

void UIButton::Release()
{
	SpriteGo::Release();
}

void UIButton::Reset()
{
	SpriteGo::Reset();
	isHover = false;
}

void UIButton::Update(float dt)
{
	sf::Vector2f mousePos = INPUT_MGR.GetMousePos();
	sf::Vector2f mouseUIPos = SCENE_MGR.GetCurrScene()->ScreenToUiPos(mousePos);

	bool prevHover = isHover;
	isHover = sprite.getGlobalBounds().contains(mouseUIPos);

	if (isHover && !prevHover)
	{
		if (OnEnter == nullptr)
			return;
		OnEnter();
	}
	if (!isHover && prevHover)
	{
		if (OnExit == nullptr)
			return;
		OnExit();
	}
	if (isHover && INPUT_MGR.GetMouseButtonUp(sf::Mouse::Left))
	{
		if (OnClick == nullptr)
			return;
		OnClick();
	}
}

void UIButton::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	window.draw(text);
}
