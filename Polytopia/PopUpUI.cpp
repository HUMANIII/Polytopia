#include "stdafx.h"
#include "PopUpUI.h"
#include "UIButton.h"
#include "MapTile.h"
#include "Unit.h"
#include "City.h"

PopUpUI::PopUpUI()
{
}

void PopUpUI::SetButtonInfo(GameObject* obj)
{
	if (static_cast<MapTile*>(obj) != nullptr)
	{

	}
	if (static_cast<Unit*>(obj) != nullptr)
	{

	}
	if (static_cast<City*>(obj) != nullptr)
	{

	}
}

void PopUpUI::Init()
{
}

void PopUpUI::Reset()
{
}

void PopUpUI::Update(float dt)
{
}

bool PopUpUI::SpecificUpdate(float dt)
{
	return false;
}

void PopUpUI::Draw(sf::RenderWindow& window)
{
}

void PopUpUI::SwitchTurn()
{
}
