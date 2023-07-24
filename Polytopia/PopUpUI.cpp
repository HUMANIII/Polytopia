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
	if (dynamic_cast<MapTile*>(obj) != nullptr)
	{
		Reset();
		MapTile* mt = dynamic_cast<MapTile*>(obj);
		//if()
		return;
	}
	if (dynamic_cast<Unit*>(obj) != nullptr)
	{
		Reset();
		Unit* unit = dynamic_cast<Unit*>(obj);
		if (unit->GetState() == Unit::State::CanMoveAtk || unit->GetState() == Unit::State::CanAtk)
		{
			UIButton* btn = new UIButton("heal");
			btn->OnClick = [unit]() { unit->Heal(); };	
			btn->sortLayer = 15;
			buttons.push_back(btn);
		}
		return;
	}
	if (dynamic_cast<City*>(obj) != nullptr)
	{
		Reset();
		City* city = dynamic_cast<City*>(obj);
		return;
	}
}

void PopUpUI::SetPosition(const sf::Vector2f& p)
{
	for (auto button : buttons)
	{
		button->SetPosition(p);
	}
}

void PopUpUI::SetPosition(float x, float y)
{
	SetPosition({ x,y });
}

void PopUpUI::CallPopUpUI(GameObject* selected)
{
	SetButtonInfo(selected);
	if (dynamic_cast<MapTile*>(selected) != nullptr)
	{
		SetPosition(dynamic_cast<MapTile*>(selected)->GetPosition());
		//if()
	}
	if (dynamic_cast<Unit*>(selected) != nullptr)
	{
		SetPosition(dynamic_cast<Unit*>(selected)->GetPosition());
	}
	if (dynamic_cast<City*>(selected) != nullptr)
	{
		SetPosition(dynamic_cast<City*>(selected)->GetPosition());
	}
}

void PopUpUI::Init()
{
}

void PopUpUI::Reset()
{
	buttons.clear();
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
