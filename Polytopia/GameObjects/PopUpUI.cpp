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
		if (mt->GetCity() == nullptr)
			return;
		if (mt->GetCity()->GetPlayer() == nullptr)
			return;
		if (mt->GetCity()->GetPlayer()->GetPlayerType() != Player::PlayerType::Player)
			return;
		//if()
		return;
	}
	if (dynamic_cast<Unit*>(obj) != nullptr)
	{
		Reset();
		Unit* unit = dynamic_cast<Unit*>(obj);
		if (unit->GetPlayerType() != Player::PlayerType::Player)
			return;
		if (unit->GetState() == Unit::State::CanNotihng)
			return;
		if (unit->CheckFullHp())
			return;
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
		//if (city->GetPlayer() == nullptr)
			//return;
		if (city->GetPlayer() == nullptr ||
			city->GetPlayer()->GetPlayerType() == Player::PlayerType::Enemy)
		{
			if (city->GetTile()->GetOnTileUnit() == nullptr)
				return;
			if (city->GetTile()->GetOnTileUnit()->GetPlayerType() != Player::PlayerType::Player
				&& city->GetTile()->GetOnTileUnit()->GetState() == Unit::State::CanMoveAtk)
				return;
			UIButton* btn = new UIButton("conquer");
			btn->OnClick = [city]() { city->Conquer(city->GetTile()->GetOnTileUnit()->GetPlayer()); };
			btn->sortLayer = 15;
			buttons.push_back(btn);
		}
		else if (city->GetPlayer()->GetPlayerType() == Player::PlayerType::Player)
		{
			UIButton* btn = new UIButton("archer");
			btn->OnClick = [city]() 
			{ 
				
				if (city->GetTile()->GetOnTileUnit() != nullptr)
				{
					std::cout << "타일에 이미 다른 유닛이 있습니다." << std::endl;
					return false;
				}
				city->GetTile()->SetUnit(city->SpawnUnit(Unit::UnitType::Archer), city->GetTile());
			std::cout << "test archer" << std::endl; 
			};
			btn->sortLayer = 15;			
			btn->AddOrigin(75, 18);
			buttons.push_back(btn);

			btn = new UIButton("defender");
			btn->OnClick = [city]() 
			{
				if (city->GetTile()->GetOnTileUnit() != nullptr)
				{
					std::cout << "타일에 이미 다른 유닛이 있습니다." << std::endl;
					return false;
				}
				city->GetTile()->SetUnit(city->SpawnUnit(Unit::UnitType::Defender), city->GetTile());
				std::cout << "test defender" << std::endl; 
			};
			btn->sortLayer = 15;
			buttons.push_back(btn);

			btn = new UIButton("knight");
			btn->OnClick = [city]() 
			{
				if (city->GetTile()->GetOnTileUnit() != nullptr)
				{
					std::cout << "타일에 이미 다른 유닛이 있습니다." << std::endl;
					return false;
				}
				city->GetTile()->SetUnit(city->SpawnUnit(Unit::UnitType::Knight), city->GetTile());
				std::cout << "test knight" << std::endl; 
			};
			btn->sortLayer = 15;
			btn->AddOrigin(-75, 18);
			buttons.push_back(btn);
		}
			return;
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
