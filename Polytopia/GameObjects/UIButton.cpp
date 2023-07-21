#include "stdafx.h"
#include "UIButton.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"

UIButton::UIButton(const std::string& n)
	:SpriteGo("", n)
{
	std::vector<std::string> infos;
	rapidcsv::Document doc("Scripts/ButtonInfoList.csv");
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<std::string>(0, i) == n)
		{
			for (int j = 0; j < doc.GetColumnCount(); j++)
			{
				infos.push_back(doc.GetCell<std::string>(j, i));
			}
		}
	}
	if(!infos.empty())
		SetButtonInfo(infos);
	sortLayer = 101;
}

UIButton::~UIButton()
{
}

void UIButton::SetButtonInfo(std::vector<std::string> infos)
{	
	sprite.setTexture(*RESOURCE_MGR.GetTexture(infos[1]));
	Utils::SetOrigin(sprite, Origins::MC);
	boundary.setTexture(*RESOURCE_MGR.GetTexture(infos[2]));
	Utils::SetOrigin(boundary, Origins::MC);
	CenterImg.setTexture(*RESOURCE_MGR.GetTexture(infos[3]));
	Utils::SetOrigin(CenterImg, Origins::MC);

	sf::Vector2f buttonSize = boundary.getOrigin() * 2.f;

	text.setFont(*RESOURCE_MGR.GetFont(infos[4]));
	text.setString(RESOURCE_MGR.GetTextList()[infos[5]]);
	text.setCharacterSize(static_cast<unsigned int>(buttonSize.y * 0.25f));
	text.setOrigin(text.getLocalBounds().width *0.5f, buttonSize.y * 1.25f);

	sprite.setColor({ static_cast<sf::Uint8>(stoi(infos[6])),static_cast<sf::Uint8>(stoi(infos[7])), 
		static_cast<sf::Uint8>(stoi(infos[8])), static_cast<sf::Uint8>(stoi(infos[9])) });
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
	window.draw(boundary);
	window.draw(CenterImg);
	window.draw(text);
}
