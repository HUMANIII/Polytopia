#include "stdafx.h"
#include "UIText.h"
#include "ResourceMgr.h"

UIText::UIText(std::string key)
{
	std::vector<std::string> infos;
	rapidcsv::Document doc("Scripts/TextUIInfoList.csv");
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<std::string>(0, i) == key)
		{
			for (int j = 1; j < doc.GetColumnCount(); j++)
			{
				infos.push_back(doc.GetCell<std::string>(j, i));
			}
		}
	}
	if (!infos.empty())
		SetTextInfo(infos);
	sortLayer = 101;
}

void UIText::SetTextInfo(std::vector<std::string> infos)
{
	origin = Origins::CUSTOM;
	mainText.setFont(*RESOURCE_MGR.GetFont(infos[3]));
	changingText.setFont(*RESOURCE_MGR.GetFont(infos[3]));
	if (stoi(infos[1]) == 1)
	{		
		img = new sf::Sprite();
		img->setTexture(*RESOURCE_MGR.GetTexture(infos[2]));		
	}
	mainText.setString(RESOURCE_MGR.GetTextList(infos[0]));
	mainText.setOrigin(mainText.getLocalBounds().width / 2, 30.f);
	if (img != nullptr)
	{
		img->setOrigin(mainText.getOrigin().x - img->getLocalBounds().width / 2.f - 5.f, mainText.getOrigin().y + 100.f);		
	}
}

void UIText::SetChangingText(int& param)
{
	textFactor = &param;
	std::stringstream ss;
	ss << (*textFactor);
	changingText.setString(ss.str());
	/*
	if(img == nullptr)
		changingText.setOrigin(changingText.getLocalBounds().width / 2.f, mainText.getOrigin().y + 5.f);
	else
		changingText.setOrigin(mainText.getOrigin().x + 5.f, mainText.getOrigin().y + 5.f);
	*/
}

void UIText::SetPosition(const sf::Vector2f& p)
{
	position = p;
	mainText.setPosition(p);
	if(img != nullptr)
		img->setPosition(p);
	changingText.setPosition(p);
}

void UIText::SetPosition(float x, float y)
{
	SetPosition({ x,y });
}

void UIText::Init()
{
}

void UIText::Reset()
{
}

void UIText::Update(float dt)
{
	std::stringstream ss;
	ss << (*textFactor);
	changingText.setString(ss.str());
}

bool UIText::SpecificUpdate(float dt)
{
	return false;
}

void UIText::Draw(sf::RenderWindow& window)
{
	window.draw(mainText);
	window.draw(changingText);
	if(img != nullptr)
		window.draw(*img);
}

void UIText::SwitchTurn()
{
}

void UIText::Release()
{
	if (img != nullptr)
	{
		delete img;
		img = nullptr;
	}
}
