#include "stdafx.h"
#include "TextUI.h"
#include "ResourceMgr.h"

TextUI::TextUI(std::string key)
{
	std::vector<std::string> infos;
	rapidcsv::Document doc("Scripts/ButtonInfoList.csv");
	for (int i = 0; i < doc.GetRowCount(); i++)
	{
		if (doc.GetCell<std::string>(0, i) == key)
		{
			for (int j = 0; j < doc.GetColumnCount(); j++)
			{
				infos.push_back(doc.GetCell<std::string>(j, i));
			}
		}
	}
	if (!infos.empty())
		SetTextInfo(infos);
	sortLayer = 101;
	
}

void TextUI::SetTextInfo(std::vector<std::string> infos)
{
	mainText.setFont(*RESOURCE_MGR.GetFont(infos[3]));
	changingText.setFont(*RESOURCE_MGR.GetFont(infos[3]));
	if (stoi(infos[1]) == 1)
	{
		img->setTexture(*RESOURCE_MGR.GetTexture(infos[2]));
	}
	mainText.setString(RESOURCE_MGR.GetTextList()[infos[0]]);
	Utils::SetOrigin(mainText, origin);
}

void TextUI::SetChangingText(int& param)
{
	
}

void TextUI::SetPosition(const sf::Vector2f& p)
{
	position = p;
	mainText.setPosition(p);
	img->setPosition(p);
	changingText.setPosition(p);
}

void TextUI::SetPosition(float x, float y)
{
	SetPosition({ x,y });
}

void TextUI::Init()
{
}

void TextUI::Reset()
{
}

void TextUI::Update(float dt)
{
}

bool TextUI::SpecificUpdate(float dt)
{
	return false;
}

void TextUI::Draw(sf::RenderWindow& window)
{
}

void TextUI::SwitchTurn()
{
}
